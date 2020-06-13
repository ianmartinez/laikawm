#ifndef LK_XWAYLAND_EVENTS_H
#define LK_XWAYLAND_EVENTS_H

#include "../xwayland/xwayland.hpp"
#include <wayland-server-core.h>

void xwayland_ready(struct wl_listener *listener, void *data);

#endif
