#include "include/cursor.hpp"

void server_cursor_motion(struct wl_listener *listener, void *data) {
    /* This event is forwarded by the cursor when a pointer emits a _relative_
	 * pointer motion event (i.e. a delta) */
    lk_server *server =
        wl_container_of(listener, server, cursor_motion);
    auto event = (struct wlr_event_pointer_motion *)data;
    /* The cursor doesn't move unless we tell it to. The cursor automatically
	 * handles constraining the motion to the output layout, as well as any
	 * special configuration applied for the specific input device which
	 * generated the event. You can pass NULL for the device if you want to move
	 * the cursor around without any input. */
    wlr_cursor_move(server->cursor, event->device,
                    event->delta_x, event->delta_y);
    server->process_cursor_motion(event->time_msec);
}

void server_cursor_motion_absolute(struct wl_listener *listener, void *data) {
    /* This event is forwarded by the cursor when a pointer emits an _absolute_
	 * motion event, from 0..1 on each axis. This happens, for example, when
	 * wlroots is running under a Wayland window rather than KMS+DRM, and you
	 * move the mouse over the window. You could enter the window from any edge,
	 * so we have to warp the mouse there. There is also some hardware which
	 * emits these events. */
    lk_server *server =
        wl_container_of(listener, server, cursor_motion_absolute);
    auto event = (struct wlr_event_pointer_motion_absolute *)data;
    wlr_cursor_warp_absolute(server->cursor, event->device, event->x, event->y);
    server->process_cursor_motion(event->time_msec);
}

void server_cursor_button(struct wl_listener *listener, void *data) {
    /* This event is forwarded by the cursor when a pointer emits a button
	 * event. */
    lk_server *server =
        wl_container_of(listener, server, cursor_button);
    auto event = (struct wlr_event_pointer_button *)data;
    /* Notify the client with pointer focus that a button press has occurred */
    wlr_seat_pointer_notify_button(server->seat,
                                   event->time_msec, event->button, event->state);
    double sx, sy;
    struct wlr_surface *surface;
    lk_view *view = server->view_at(server->cursor->x, server->cursor->y, &surface, &sx, &sy);
    if (event->state == WLR_BUTTON_RELEASED) {
        /* If you released any buttons, we exit interactive move/resize mode. */
        server->cursor_mode = LK_CURSOR_PASSTHROUGH;
    } else if (view != NULL) {
        /* Focus that client if the button was _pressed_ */
        view->focus(surface);
    }
}

void server_cursor_axis(struct wl_listener *listener, void *data) {
    /* This event is forwarded by the cursor when a pointer emits an axis event,
	 * for example when you move the scroll wheel. */
    lk_server *server =
        wl_container_of(listener, server, cursor_axis);
    auto event = (struct wlr_event_pointer_axis *)data;
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
    lk_server *server =
        wl_container_of(listener, server, cursor_frame);
    /* Notify the client with pointer focus of the frame event. */
    wlr_seat_pointer_notify_frame(server->seat);
}

void seat_request_cursor(struct wl_listener *listener, void *data) {
    lk_server *server = wl_container_of(
        listener, server, request_cursor);
    /* This event is rasied by the seat when a client provides a cursor image */
    auto event = (struct wlr_seat_pointer_request_set_cursor_event *)data;
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