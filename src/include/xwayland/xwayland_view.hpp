#ifndef LK_XWAYLAND_VIEW_H
#define LK_XWAYLAND_VIEW_H

#include "../wl_includes.hpp"
#include "../view.hpp"
#include "xwayland.hpp"
#include <xcb/xproto.h>
#include "../widgets/sizing.hpp"

#define class class_
#define namespace namespace_
#define static

extern "C" {
#include <wlr/xwayland.h>
#include <wlr/xcursor.h>
}

#undef static
#undef class
#undef namespace

class lk_xwayland_view : public lk_view {
    public:
        lk_view_constraints get_constraints();
        
        struct wl_listener request_configure;
        struct wl_listener request_fullscreen;
        struct wl_listener request_activate;
        struct wl_listener request_move;
        struct wl_listener request_resize;
        struct wl_listener set_title;
        struct wl_listener set_class;
        struct wl_listener set_role;
        struct wl_listener set_window_type;
        struct wl_listener set_hints;
        struct wl_listener set_decorations;
};

#endif

