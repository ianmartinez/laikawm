#ifndef LK_RENDER_H
#define LK_RENDER_H

#include "os.hpp"
#include <unistd.h>
#include <time.h>
#include <wayland-server-core.h>
#include <wayland-util.h>
#include "server.hpp"
#include "output.hpp"

/* Used to move all of the data necessary to render a surface from the top-level
 * frame handler to the per-surface render function. */
struct lk_render_data {
	struct wlr_output *output;
	struct wlr_renderer *renderer;
	struct lk_view *view;
	struct timespec *when;
};

void render_surface(struct wlr_surface *surface,int sx, int sy, void *data);

#endif