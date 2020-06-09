#include "cursor.h"

void server_new_pointer(struct lk_server *server,
                        struct wlr_input_device *device) {
    /* We don't do anything special with pointers. All of our pointer handling
	 * is proxied through wlr_cursor. On another compositor, you might take this
	 * opportunity to do libinput configuration on the device to set
	 * acceleration, etc. */
    wlr_cursor_attach_input_device(server->cursor, device);
}

void process_cursor_move(struct lk_server *server, uint32_t time) {
    /* Move the grabbed view to the new position. */
    server->grabbed_view->x = server->cursor->x - server->grab_x;
    server->grabbed_view->y = server->cursor->y - server->grab_y;
}

void process_cursor_resize(struct lk_server *server, uint32_t time) {
    /*
	 * Resizing the grabbed view can be a little bit complicated, because we
	 * could be resizing from any corner or edge. This not only resizes the view
	 * on one or two axes, but can also move the view if you resize from the top
	 * or left edges (or top-left corner).
	 *
	 * Note that I took some shortcuts here. In a more fleshed-out compositor,
	 * you'd wait for the client to prepare a buffer at the new size, then
	 * commit any movement that was prepared.
	 */
    struct lk_view *view = server->grabbed_view;
    double border_x = server->cursor->x - server->grab_x;
    double border_y = server->cursor->y - server->grab_y;
    int new_left = server->grab_geobox.x;
    int new_right = server->grab_geobox.x + server->grab_geobox.width;
    int new_top = server->grab_geobox.y;
    int new_bottom = server->grab_geobox.y + server->grab_geobox.height;

    if (server->resize_edges & WLR_EDGE_TOP) {
        new_top = border_y;
        if (new_top >= new_bottom) {
            new_top = new_bottom - 1;
        }
    } else if (server->resize_edges & WLR_EDGE_BOTTOM) {
        new_bottom = border_y;
        if (new_bottom <= new_top) {
            new_bottom = new_top + 1;
        }
    }
    if (server->resize_edges & WLR_EDGE_LEFT) {
        new_left = border_x;
        if (new_left >= new_right) {
            new_left = new_right - 1;
        }
    } else if (server->resize_edges & WLR_EDGE_RIGHT) {
        new_right = border_x;
        if (new_right <= new_left) {
            new_right = new_left + 1;
        }
    }

    struct wlr_box geo_box;
    wlr_xdg_surface_get_geometry(view->xdg_surface, &geo_box);
    view->x = new_left - geo_box.x;
    view->y = new_top - geo_box.y;

    int new_width = new_right - new_left;
    int new_height = new_bottom - new_top;
    wlr_xdg_toplevel_set_size(view->xdg_surface, new_width, new_height);
}

void process_cursor_motion(struct lk_server *server, uint32_t time) {
    /* If the mode is non-passthrough, delegate to those functions. */
    if (server->has_grabbed_view) {
        if (server->cursor_mode == LK_CURSOR_MOVE) {
            process_cursor_move(server, time);
            return;
        } else if (server->cursor_mode == LK_CURSOR_RESIZE) {
            process_cursor_resize(server, time);
            return;
        }
    }

    /* Otherwise, find the view under the pointer and send the event along. */
    double sx, sy;
    struct wlr_seat *seat = server->seat;
    struct wlr_surface *surface = NULL;
    struct lk_view *view = desktop_view_at(server,
                                           server->cursor->x, server->cursor->y, &surface, &sx, &sy);
    if (!view) {
        /* If there's no view under the cursor, set the cursor image to a
		 * default. This is what makes the cursor image appear when you move it
		 * around the screen, not over any views. */
        wlr_xcursor_manager_set_cursor_image(
            server->cursor_mgr, "left_ptr", server->cursor);
    }
    if (surface) {
        bool focus_changed = seat->pointer_state.focused_surface != surface;
        /*
		 * "Enter" the surface if necessary. This lets the client know that the
		 * cursor has entered one of its surfaces.
		 *
		 * Note that this gives the surface "pointer focus", which is distinct
		 * from keyboard focus. You get pointer focus by moving the pointer over
		 * a window.
		 */
        wlr_seat_pointer_notify_enter(seat, surface, sx, sy);
        if (!focus_changed) {
            /* The enter event contains coordinates, so we only need to notify
			 * on motion if the focus did not change. */
            wlr_seat_pointer_notify_motion(seat, time, sx, sy);
        }
    } else {
        /* Clear pointer focus so future button events and such are not sent to
		 * the last client to have the cursor over it. */
        wlr_seat_pointer_clear_focus(seat);
    }
}

void server_cursor_motion(struct wl_listener *listener, void *data) {
    /* This event is forwarded by the cursor when a pointer emits a _relative_
	 * pointer motion event (i.e. a delta) */
    struct lk_server *server =
        wl_container_of(listener, server, cursor_motion);
    struct wlr_event_pointer_motion *event = data;
    /* The cursor doesn't move unless we tell it to. The cursor automatically
	 * handles constraining the motion to the output layout, as well as any
	 * special configuration applied for the specific input device which
	 * generated the event. You can pass NULL for the device if you want to move
	 * the cursor around without any input. */
    wlr_cursor_move(server->cursor, event->device,
                    event->delta_x, event->delta_y);
    process_cursor_motion(server, event->time_msec);
}

void server_cursor_motion_absolute(struct wl_listener *listener, void *data) {
    /* This event is forwarded by the cursor when a pointer emits an _absolute_
	 * motion event, from 0..1 on each axis. This happens, for example, when
	 * wlroots is running under a Wayland window rather than KMS+DRM, and you
	 * move the mouse over the window. You could enter the window from any edge,
	 * so we have to warp the mouse there. There is also some hardware which
	 * emits these events. */
    struct lk_server *server =
        wl_container_of(listener, server, cursor_motion_absolute);
    struct wlr_event_pointer_motion_absolute *event = data;
    wlr_cursor_warp_absolute(server->cursor, event->device, event->x, event->y);
    process_cursor_motion(server, event->time_msec);
}

void server_cursor_button(struct wl_listener *listener, void *data) {
    /* This event is forwarded by the cursor when a pointer emits a button
	 * event. */
    struct lk_server *server =
        wl_container_of(listener, server, cursor_button);
    struct wlr_event_pointer_button *event = data;
    /* Notify the client with pointer focus that a button press has occurred */
    wlr_seat_pointer_notify_button(server->seat,
                                   event->time_msec, event->button, event->state);
    double sx, sy;
    struct wlr_surface *surface;
    struct lk_view *view = desktop_view_at(server,
                                           server->cursor->x, server->cursor->y, &surface, &sx, &sy);
    if (event->state == WLR_BUTTON_RELEASED) {
        /* If you released any buttons, we exit interactive move/resize mode. */
        server->cursor_mode = LK_CURSOR_PASSTHROUGH;
    } else {
        /* Focus that client if the button was _pressed_ */
        focus_view(view, surface);
    }
}

void server_cursor_axis(struct wl_listener *listener, void *data) {
    /* This event is forwarded by the cursor when a pointer emits an axis event,
	 * for example when you move the scroll wheel. */
    struct lk_server *server =
        wl_container_of(listener, server, cursor_axis);
    struct wlr_event_pointer_axis *event = data;
    /* Notify the client with pointer focus of the axis event. */
    wlr_seat_pointer_notify_axis(server->seat,
                                 event->time_msec, event->orientation, event->delta,
                                 event->delta_discrete, event->source);
}

void server_cursor_frame(struct wl_listener *listener, void *data) {
    /* This event is forwarded by the cursor when a pointer emits an frame
	 * event. Frame events are sent after regular pointer events to group
	 * multiple events together. For instance, two axis events may happen at the
	 * same time, in which case a frame event won't be sent in between. */
    struct lk_server *server =
        wl_container_of(listener, server, cursor_frame);
    /* Notify the client with pointer focus of the frame event. */
    wlr_seat_pointer_notify_frame(server->seat);
}

void seat_request_cursor(struct wl_listener *listener, void *data) {
    struct lk_server *server = wl_container_of(
        listener, server, request_cursor);
    /* This event is rasied by the seat when a client provides a cursor image */
    struct wlr_seat_pointer_request_set_cursor_event *event = data;
    struct wlr_seat_client *focused_client =
        server->seat->pointer_state.focused_client;
    /* This can be sent by any client, so we check to make sure this one is
	 * actually has pointer focus first. */
    if (focused_client == event->seat_client) {
        /* Once we've vetted the client, we can tell the cursor to use the
		 * provided surface as the cursor image. It will set the hardware cursor
		 * on the output that it's currently on and continue to do so as the
		 * cursor moves between outputs. */
        wlr_cursor_set_surface(server->cursor, event->surface,
                               event->hotspot_x, event->hotspot_y);
    }
}