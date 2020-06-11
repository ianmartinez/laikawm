#ifndef LK_OUTPUT_H
#define LK_OUTPUT_H

#include <stdlib.h>
#include <time.h>
#include <wayland-server-core.h>
#include <wayland-util.h>

#include "background.hpp"
#include "color.hpp"
#include "os.hpp"
#include "render.hpp"
#include "server.hpp"
#include "wl_includes.hpp"

struct lk_output {
	struct wl_list link;
	lk_server *server;
	struct wlr_output *wlr_output;
	struct wl_listener frame;
};

void output_add(struct wl_listener *listener, void *data);
void output_frame(struct wl_listener *listener, void *data);

#endif
