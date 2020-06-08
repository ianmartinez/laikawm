#ifndef LK_KEYBOARD_H
#define LK_KEYBOARD_H

#include <stdlib.h> 
#include <wayland-server-core.h>
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

void keyboard_handle_modifiers(struct wl_listener *listener, void *data);
bool handle_keybinding(struct lk_server *server, xkb_keysym_t sym);
void keyboard_handle_key(struct wl_listener *listener, void *data);
void server_new_keyboard(struct lk_server *server, struct wlr_input_device *device);

#endif
