#ifndef LK_SEAT_EVENTS_H
#define LK_SEAT_EVENTS_H

#include <wayland-server-core.h>
#include <wayland-util.h>

#include "../server.hpp"
#include "../wl_includes.hpp"

void seat_request_set_selection(struct wl_listener *listener, void *data);

#endif
