#ifndef LK_KEYBOARD_H
#define LK_KEYBOARD_H

#include <stdlib.h>
#include <wayland-server-core.h>
#include <wayland-util.h>

#include "../server.hpp"
#include "../wl_includes.hpp"

class lk_server;

class lk_keyboard {
    public:
        lk_server *server;
        struct wlr_input_device *device;

        struct wl_listener modifiers;
        struct wl_listener key;
};

#endif

