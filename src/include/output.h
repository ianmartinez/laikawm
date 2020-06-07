#ifndef LK_OUTPUT_H
#define LK_OUTPUT_H

#include <wayland-util.h>
#include <wlr/types/wlr_output.h>
#include "server.h"

struct lk_output {
	struct wl_list link;
	struct lk_server *server;
	struct wlr_output *wlr_output;
	struct wl_listener frame;
};

#endif