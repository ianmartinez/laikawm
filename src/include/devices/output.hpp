#ifndef LK_OUTPUT_H
#define LK_OUTPUT_H

#include "../os.hpp"

#include <stdlib.h>
#include <time.h>
#include <wayland-server-core.h>
#include <wayland-util.h>

#include "../render.hpp"
#include "../server.hpp"
#include "../wl_includes.hpp"

class lk_output {
    public:
        lk_server *server;
        struct wlr_output *wlr_output;
        struct wl_listener frame;
};

#endif
