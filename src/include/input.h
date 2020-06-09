#ifndef LK_INPUT_H
#define LK_INPUT_H

#include <wayland-server-core.h>

#include "cursor.h"
#include "keyboard.h"

/**
 * Route a new input to a handler function. Right now, the only inputs
 * are cursor and keyboard.
 */
void server_new_input(struct wl_listener *listener, void *data);

#endif