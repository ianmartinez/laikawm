#ifndef LK_INPUT_EVENTS_H
#define LK_INPUT_EVENTS_H

#include <wayland-server-core.h>

#include "cursor_events.hpp"
#include "../keyboard.hpp"

/**
 * Route a new input to a handler function. Right now, the only inputs
 * are cursor and keyboard.
 */
void server_new_input(struct wl_listener *listener, void *data);

#endif
