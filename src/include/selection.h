#ifndef LK_SELECTION_H
#define LK_SELECTION_H

#include <wayland-server-core.h>
#include <wayland-util.h>
#include <wlr/types/wlr_data_device.h>

#include "server.h"

void seat_request_set_selection(struct wl_listener *listener, void *data);

#endif