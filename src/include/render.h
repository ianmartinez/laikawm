#ifndef LK_RENDER_H
#define LK_RENDER_H

#include "os.h"
#include <unistd.h>
#include <time.h>
#include <wayland-server-core.h>
#include <wayland-util.h>
#include <wlr/types/wlr_output.h>
#include <wlr/render/wlr_renderer.h>
#include "server.h"

struct lk_output {
	struct wl_list link;
	struct lk_server *server;
	struct wlr_output *wlr_output;
	struct wl_listener frame;
};

/* Used to move all of the data necessary to render a surface from the top-level
 * frame handler to the per-surface render function. */
struct lk_render_data {
	struct wlr_output *output;
	struct wlr_renderer *renderer;
	struct lk_view *view;
	struct timespec *when;
};

void render_surface(struct wlr_surface *surface,int sx, int sy, void *data);
void output_frame(struct wl_listener *listener, void *data);

#endif