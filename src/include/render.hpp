#ifndef LK_RENDER_H
#define LK_RENDER_H

#include <time.h>
#include <unistd.h>
#include <wayland-server-core.h>
#include <wayland-util.h>

#include "os.hpp"
#include "devices/output.hpp"
#include "server.hpp"
#include "wl_includes.hpp"

class lk_view;

/* Used to move all of the data necessary to render a surface from the top-level
 * frame handler to the per-surface render function. */
class lk_render_data {
    public:
        lk_output *output;
        struct wlr_renderer *renderer;
        lk_view *view;
        struct timespec *when;
};

void render_surface(struct wlr_surface *surface, int sx, int sy, void *data);

#endif
