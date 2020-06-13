#ifndef LK_XWAYLAND_H
#define LK_XWAYLAND_H

#include "../wl_includes.hpp"
#include <xcb/xproto.h>

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

enum lk_xwayland_atom_name {
    NET_WM_WINDOW_TYPE_NORMAL,
    NET_WM_WINDOW_TYPE_DIALOG,
    NET_WM_WINDOW_TYPE_UTILITY,
    NET_WM_WINDOW_TYPE_TOOLBAR,
    NET_WM_WINDOW_TYPE_SPLASH,
    NET_WM_WINDOW_TYPE_MENU,
    NET_WM_WINDOW_TYPE_DROPDOWN_MENU,
    NET_WM_WINDOW_TYPE_POPUP_MENU,
    NET_WM_WINDOW_TYPE_TOOLTIP,
    NET_WM_WINDOW_TYPE_NOTIFICATION,
    NET_WM_STATE_MODAL
};

class lk_xwayland {
    public:
        struct wlr_xwayland *wlr_xwayland;
        struct wlr_xcursor_manager *xcursor_manager;
};

#endif
