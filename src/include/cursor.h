#ifndef LK_CURSOR_H
#define LK_CURSOR_H

#include <wayland-server-core.h>
#include "cursormode.h"
#include "server.h"
#include "view.h"

void process_cursor_move(struct lk_server *server, uint32_t time);
void process_cursor_resize(struct lk_server *server, uint32_t time);
void process_cursor_motion(struct lk_server *server, uint32_t time);
void server_cursor_motion(struct wl_listener *listener, void *data);
void server_cursor_motion_absolute(struct wl_listener *listener, void *data);
void server_cursor_button(struct wl_listener *listener, void *data);
void server_cursor_axis(struct wl_listener *listener, void *data);
void server_cursor_frame(struct wl_listener *listener, void *data);

#endif