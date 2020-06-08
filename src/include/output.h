#ifndef LK_OUTPUT_H
#define LK_OUTPUT_H

#include "os.h"
#include <stdlib.h>
#include <time.h>
#include <wayland-server-core.h>
#include <wayland-util.h>
#include <wlr/types/wlr_output.h>
#include "server.h"
#include "render.h"
#include "color.h"
#include "desktop.h"

struct lk_output {
	struct wl_list link;
	struct lk_server *server;
	struct wlr_output *wlr_output;
	struct wl_listener frame;
};

void output_add(struct wl_listener *listener, void *data);
void output_frame(struct wl_listener *listener, void *data);

#endif