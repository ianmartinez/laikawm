#ifndef LK_VIEW_H
#define LK_VIEW_H

#include <wayland-util.h>

#include "server.hpp"
#include "wl_includes.hpp"
#include "widgets/sizing.hpp"

class lk_server;

enum lk_view_type {
    LK_XDG_VIEW,
    LK_XWAYLAND_VIEW,
    LK_LAYER_VIEW
};

class lk_view {
    public:
        virtual ~lk_view();

        lk_server *server;
        lk_view_type view_type;
        struct wlr_xdg_surface *xdg_surface;

        /**
         * Events
         */
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
        void map_surface(struct wlr_surface *wlr_surface,
                        bool fullscreen, struct wlr_output *fullscreen_output,
                        bool decoration);
        virtual lk_view_constraints get_constraints();
};

#endif

