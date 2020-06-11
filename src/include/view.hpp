#ifndef LK_VIEW_H
#define LK_VIEW_H

#include <wayland-util.h>

#include "server.hpp"
#include "wl_includes.hpp"

class lk_server;

class lk_view {
    public:
        struct wl_list link;
        lk_server *server;
        struct wlr_xdg_surface *xdg_surface;
        struct wl_listener map;
        struct wl_listener unmap;
        struct wl_listener destroy;
        struct wl_listener request_move;
        struct wl_listener request_resize;
        bool mapped;
        int x, y;

        bool exists_at(double lx, double ly, struct wlr_surface **surface,
                       double *sx, double *sy);

        void focus(struct wlr_surface *surface);

        void request_cursor_operation(enum lk_cursor_mode mode, uint32_t edges);
        void move_with_cursor();
        void resize_with_cursor(uint32_t edges);
};

#endif
