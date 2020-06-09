#ifndef LK_VIEW_H
#define LK_VIEW_H

#include <wayland-util.h>
#include <wlr/types/wlr_output.h>
#include <wlr/types/wlr_xdg_shell.h>

#include "server.h"

struct lk_view {
    struct wl_list link;
    struct lk_server *server;
    struct wlr_xdg_surface *xdg_surface;
    struct wl_listener map;
    struct wl_listener unmap;
    struct wl_listener destroy;
    struct wl_listener request_move;
    struct wl_listener request_resize;
    bool mapped;
    int x, y;
};

struct lk_view *desktop_view_at(
    struct lk_server *server, double lx, double ly,
    struct wlr_surface **surface, double *sx, double *sy);

bool view_at(struct lk_view *view,
             double lx, double ly, struct wlr_surface **surface,
             double *sx, double *sy);

void focus_view(struct lk_view *view, struct wlr_surface *surface);

#endif