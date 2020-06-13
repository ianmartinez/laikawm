#include "../include/events/keyboard_events.hpp"

void keyboard_handle_modifiers(struct wl_listener *listener, void *data) {
    /* This event is raised when a modifier key, such as shift or alt, is
     * pressed. We simply communicate this to the client. */
    lk_keyboard *keyboard = wl_container_of(listener, keyboard, modifiers);
    /*
     * A seat can only have one keyboard, but this is a limitation of the
     * Wayland protocol - not wlroots. We assign all connected keyboards to the
     * same seat. You can swap out the underlying wlr_keyboard like this and
     * wlr_seat handles this transparently.
     */
    wlr_seat_set_keyboard(keyboard->server->seat, keyboard->device);
    /* Send modifiers to the client. */
    wlr_seat_keyboard_notify_modifiers(keyboard->server->seat,
                                       &keyboard->device->keyboard->modifiers);
}

void keyboard_handle_key(struct wl_listener *listener, void *data) {
    /* This event is raised when a key is pressed or released. */
    lk_keyboard *keyboard = wl_container_of(listener, keyboard, key);
    lk_server *server = keyboard->server;
    auto event = (struct wlr_event_keyboard_key *)data;
    struct wlr_seat *seat = server->seat;

    /* Translate libinput keycode -> xkbcommon */
    uint32_t keycode = event->keycode + 8;

    /* Get a list of keysyms based on the keymap for this keyboard */
    const xkb_keysym_t *syms;
    int nsyms =
        xkb_state_key_get_syms(keyboard->device->keyboard->xkb_state, keycode, &syms);

    bool handled = false;
    uint32_t modifiers = wlr_keyboard_get_modifiers(keyboard->device->keyboard);
    if (event->state == WLR_KEY_PRESSED) {
        /* If alt is held down and this button was _pressed_, we attempt to
         * process it as a compositor keybinding. */
        if ((modifiers & WLR_MODIFIER_LOGO)) {
            for (int i = 0; i < nsyms; i++) {
                handled = server->handle_keybinding(modifiers, syms[i]);
            }
        }
    }

    if (!handled) {
        /* Otherwise, we pass it along to the client. */
        wlr_seat_set_keyboard(seat, keyboard->device);
        wlr_seat_keyboard_notify_key(seat, event->time_msec,
                                     event->keycode, event->state);
    }
}


