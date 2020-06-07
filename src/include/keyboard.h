#ifndef LK_KEYBOARD_H
#define LK_KEYBOARD_H

#include <wayland-util.h>
#include <wlr/types/wlr_input_device.h>
#include "server.h"

struct lk_keyboard {
	struct wl_list link;
	struct lk_server *server;
	struct wlr_input_device *device;

	struct wl_listener modifiers;
	struct wl_listener key;
};

#endif
