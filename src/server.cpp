#include "include/server.hpp"

#include "include/keyboard.hpp"

lk_view *lk_server::view_at(double lx, double ly, struct wlr_surface **surface,
                            double *sx, double *sy) {
    /* This iterates over all of our surfaces and attempts to find one under the
	 * cursor. This relies on this->views being ordered from top-to-bottom. */

    for (auto it = views.begin(); it != views.end(); ++it) {
        lk_view *view = *it;
        if (view->exists_at(lx, ly, surface, sx, sy)) {
            return view;
        }
    }

    return NULL;
}

void lk_server::pointer_added(struct wlr_input_device *device) {
    /* We don't do anything special with pointers. All of our pointer handling
	 * is proxied through wlr_cursor. On another compositor, you might take this
	 * opportunity to do libinput configuration on the device to set
	 * acceleration, etc. */
    wlr_cursor_attach_input_device(this->cursor, device);
}

void lk_server::cursor_move_view(uint32_t time) {
    /* Move the grabbed view to the new position. */
    this->grabbed_view->x = this->cursor->x - this->grab_x;
    this->grabbed_view->y = this->cursor->y - this->grab_y;
}

void lk_server::cursor_resize_view(uint32_t time) {
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
    lk_view *view = this->grabbed_view;
    double border_x = this->cursor->x - this->grab_x;
    double border_y = this->cursor->y - this->grab_y;
    int new_left = this->grab_geobox.x;
    int new_right = this->grab_geobox.x + this->grab_geobox.width;
    int new_top = this->grab_geobox.y;
    int new_bottom = this->grab_geobox.y + this->grab_geobox.height;

    if (this->resize_edges & WLR_EDGE_TOP) {
        new_top = border_y;
        if (new_top >= new_bottom) {
            new_top = new_bottom - 1;
        }
    } else if (this->resize_edges & WLR_EDGE_BOTTOM) {
        new_bottom = border_y;
        if (new_bottom <= new_top) {
            new_bottom = new_top + 1;
        }
    }
    if (this->resize_edges & WLR_EDGE_LEFT) {
        new_left = border_x;
        if (new_left >= new_right) {
            new_left = new_right - 1;
        }
    } else if (this->resize_edges & WLR_EDGE_RIGHT) {
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

void lk_server::process_cursor_motion(uint32_t time) {
    /* If the mode is non-passthrough, delegate to those functions. */
    if (this->has_grabbed_view) {
        if (this->cursor_mode == LK_CURSOR_MOVE) {
            this->cursor_move_view(time);
            return;
        } else if (this->cursor_mode == LK_CURSOR_RESIZE) {
            this->cursor_resize_view(time);
            return;
        }
    }

    /* Otherwise, find the view under the pointer and send the event along. */
    double sx, sy;
    struct wlr_seat *seat = this->seat;
    struct wlr_surface *surface = NULL;
    lk_view *view_under_cursor =
        this->view_at(this->cursor->x, this->cursor->y, &surface, &sx, &sy);

    if (view_under_cursor == NULL) {
        /* If there's no view under the cursor, set the cursor image to a
		 * default. This is what makes the cursor image appear when you move it
		 * around the screen, not over any views. */
        wlr_xcursor_manager_set_cursor_image(this->cursor_mgr, "left_ptr", this->cursor);
    }

    if (surface != NULL) {
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

void lk_server::keyboard_added(struct wlr_input_device *device) {
    auto keyboard = (struct lk_keyboard *)calloc(1, sizeof(struct lk_keyboard));
    keyboard->server = this;
    keyboard->device = device;

    /* We need to prepare an XKB keymap and assign it to the keyboard. This
	 * assumes the defaults (e.g. layout = "us"). */
    struct xkb_rule_names rules = {0};
    struct xkb_context *context = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
    struct xkb_keymap *keymap = xkb_map_new_from_names(context, &rules, XKB_KEYMAP_COMPILE_NO_FLAGS);

    wlr_keyboard_set_keymap(device->keyboard, keymap);
    xkb_keymap_unref(keymap);
    xkb_context_unref(context);
    wlr_keyboard_set_repeat_info(device->keyboard, 25, 600);

    /* Here we set up listeners for keyboard events. */
    keyboard->modifiers.notify = keyboard_handle_modifiers;
    wl_signal_add(&device->keyboard->events.modifiers, &keyboard->modifiers);
    keyboard->key.notify = keyboard_handle_key;
    wl_signal_add(&device->keyboard->events.key, &keyboard->key);

    wlr_seat_set_keyboard(this->seat, device);

    /* And add the keyboard to our list of keyboards */
    wl_list_insert(&this->keyboards, &keyboard->link);
}

void lk_server::launch_program(std::string program_name) {
    auto prog_launch_cmd = "WAYLAND_DISPLAY=" + this->display_socket + " " + program_name + " &";
    wlr_log(WLR_INFO, "Launching %s:\n%s", program_name.c_str(), prog_launch_cmd.c_str());

    system(prog_launch_cmd.c_str());
}

bool lk_server::handle_keybinding(uint32_t modifiers, xkb_keysym_t sym) {
    /*
	 * Here we handle compositor keybindings. This is when the compositor is
	 * processing keys, rather than passing them on to the client for its own
	 * processing.
	 *
	 * This function assumes LOGO is held down.
	 */
    switch (sym) {
        case XKB_KEY_Escape:  // LOGO + ESC = Kill LaikaWM
            wl_display_terminate(this->wl_display);
            break;
        case XKB_KEY_n:  // Nemo is a good test program
            launch_program("nemo");
            break;
        case XKB_KEY_c:  // As is gnome-terminal
            launch_program("gnome-terminal");
            break;
        default:
            return false;
    }

    return true;
}