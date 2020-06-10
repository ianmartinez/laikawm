#ifndef LK_KEYBOARD_H
#define LK_KEYBOARD_H

#include <stdlib.h>
#include <wayland-server-core.h>
#include <wayland-util.h>

#include "server.hpp"
#include "wl_includes.hpp"

struct lk_keyboard {
    struct wl_list link;
    lk_server *server;
    struct wlr_input_device *device;

    struct wl_listener modifiers;
    struct wl_listener key;
};

void keyboard_handle_modifiers(struct wl_listener *listener, void *data);
void keyboard_handle_key(struct wl_listener *listener, void *data);

#endif
