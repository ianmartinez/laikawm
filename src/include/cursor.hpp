#ifndef LK_CURSOR_H
#define LK_CURSOR_H

#include <wayland-server-core.h>

#include "cursor_mode.hpp"
#include "server.hpp"
#include "view.hpp"

void server_cursor_motion(struct wl_listener *listener, void *data);
void server_cursor_motion_absolute(struct wl_listener *listener, void *data);
void server_cursor_button(struct wl_listener *listener, void *data);
void server_cursor_axis(struct wl_listener *listener, void *data);
void server_cursor_frame(struct wl_listener *listener, void *data);
void seat_request_cursor(struct wl_listener *listener, void *data);

#endif
