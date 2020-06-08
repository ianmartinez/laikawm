#ifndef LK_OUTPUT_H
#define LK_OUTPUT_H

#include "os.hpp"
#include <stdlib.h>
#include <time.h>
#include <wayland-server-core.h>
#include <wayland-util.h>
#include "server.hpp"
#include "render.hpp"
#include "color.hpp"
#include "desktop.hpp"

struct lk_output {
	struct wl_list link;
	struct lk_server *server;
	struct wlr_output *wlr_output;
	struct wl_listener frame;
};

void output_add(struct wl_listener *listener, void *data);
void output_frame(struct wl_listener *listener, void *data);

#endif