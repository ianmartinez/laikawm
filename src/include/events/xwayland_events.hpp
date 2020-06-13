#ifndef LK_XWAYLAND_EVENTS_H
#define LK_XWAYLAND_EVENTS_H

#include "../wl_includes.hpp"
#include "../xwayland/xwayland.hpp"
#include <wayland-server-core.h>

void xwayland_ready(struct wl_listener *listener, void *data);
void xwayland_new_surface(struct wl_listener *listener, void *data);

#endif
