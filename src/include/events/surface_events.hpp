#ifndef LK_SURFACE_EVENTS_H
#define LK_SURFACE_EVENTS_H

#include <stdlib.h>
#include <wayland-server-core.h>

#include "../server.hpp"
#include "view_events.hpp"

void surface_map(struct wl_listener *listener, void *data);
void surface_unmap(struct wl_listener *listener, void *data);
void surface_destroy(struct wl_listener *listener, void *data);
void surface_recieved(struct wl_listener *listener, void *data);

#endif
