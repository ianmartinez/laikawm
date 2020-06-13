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
};

#endif

