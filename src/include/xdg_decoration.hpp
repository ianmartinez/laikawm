#ifndef LK_WINDOW_DECORATION_H
#define LK_WINDOW_DECORATION_H

#include <list>

#include "server.hpp"
#include "wl_includes.hpp"
#include <wlr/types/wlr_xdg_decoration_v1.h>

class lk_server_decoration {
    public:
        lk_server *server;
        struct wlr_server_decoration *wlr_server_decoration;

        struct wl_listener destroy;
        struct wl_listener mode;

        ~lk_server_decoration();
};

class lk_decoration_manager {
    public:
        lk_server *server;

        struct wlr_server_decoration_manager *server_decoration_manager;
        struct wl_listener server_decoration;

        struct std::list<lk_server_decoration *> decorations;
};

#endif
