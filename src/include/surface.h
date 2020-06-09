#ifndef LK_SURFACE_H
#define LK_SURFACE_H

#include <stdlib.h>
#include <wayland-server-core.h>

#include "server.h"
#include "view_operations.h"

void surface_map(struct wl_listener *listener, void *data);
void surface_unmap(struct wl_listener *listener, void *data);
void surface_destroy(struct wl_listener *listener, void *data);
void surface_recieved(struct wl_listener *listener, void *data);

#endif