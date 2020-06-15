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

class lk_server;

class lk_output {
    public:
        lk_server *server;
        struct wlr_output *wlr_output;
        struct wl_listener frame;
        
        void render_rect(struct wlr_box *box, lk_color *color, float scale);
        void render_rect_outline(struct wlr_box *box, lk_color *color, float width, float scale);
        
        /**
         * Scale a box at a scale.
         */
        static void scale_box(wlr_box *box, wlr_box *scaled_box, float scale);
                
        /**
         * Scale a box at this output's scale.
         */
        void scale_box(wlr_box *box, wlr_box *scaled_box);
};

#endif
