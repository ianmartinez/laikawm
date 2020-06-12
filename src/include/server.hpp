#ifndef LK_SERVER_H
#define LK_SERVER_H

#include <wayland-server-core.h>
#include <wayland-server-protocol.h>

#include <list>

#include "theme/desktop.hpp"
#include "cursor_mode.hpp"
#include "view.hpp"
#include "wl_includes.hpp"
#include "events/keyboard_events.hpp"
#include "devices/keyboard.hpp"

class lk_view;
class lk_keyboard;

class lk_server {
    public:
        struct wl_display *wl_display;
        std::string display_socket;
        struct wlr_backend *backend;
        struct wlr_renderer *renderer;
        struct wlr_compositor *compositor;

        struct wlr_xdg_shell *xdg_shell;
        struct wl_listener new_xdg_surface;
        struct wlr_layer_shell_v1 *layer_shell;
        struct wl_listener layer_shell_surface;
        std::list<lk_view *> views;

        struct wlr_cursor *cursor;
        struct wlr_xcursor_manager *cursor_mgr;
        struct wl_listener cursor_motion;
        struct wl_listener cursor_motion_absolute;
        struct wl_listener cursor_button;
        struct wl_listener cursor_axis;
        struct wl_listener cursor_frame;

        struct wlr_seat *seat;
        struct wl_listener new_input;
        struct wl_listener request_cursor;
        struct wl_listener request_set_selection;
        std::list<lk_keyboard *> keyboards;
        
        enum lk_cursor_mode cursor_mode;
        bool has_grabbed_view;
        lk_view *grabbed_view;
        double grab_x, grab_y;
        struct wlr_box grab_geobox;
        uint32_t resize_edges;

        struct wlr_output_layout *output_layout;
        struct wl_list outputs;
        struct wl_listener new_output;

        lk_desktop desktop;

        lk_view *view_at(double lx, double ly, struct wlr_surface **surface,
                         double *sx, double *sy);
        void launch_program(std::string program_name);

        /**
         * Mouse
         */
        void pointer_added(struct wlr_input_device *device);
        void cursor_move_view(uint32_t time);
        void cursor_resize_view(uint32_t time);
        void process_cursor_motion(uint32_t time);

        /**
         * Keyboard
         */
        bool handle_keybinding(uint32_t modifiers, xkb_keysym_t sym);
        void keyboard_added(struct wlr_input_device *device);
};

#endif
