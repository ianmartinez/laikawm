#ifndef LK_KEYBOARD_EVENTS_H
#define LK_KEYBOARD_EVENTS_H

#include <wayland-server-core.h>
#include "../server.hpp"
#include "../wl_includes.hpp"
#include "../keyboard.hpp"

void keyboard_handle_modifiers(struct wl_listener *listener, void *data);
void keyboard_handle_key(struct wl_listener *listener, void *data);

#endif
