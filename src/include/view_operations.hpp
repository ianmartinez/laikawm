#ifndef LK_VIEW_OPERATION_H
#define LK_VIEW_OPERATION_H

#include <wayland-util.h>

#include "cursor_mode.hpp"
#include "server.hpp"
#include "view.hpp"

void view_request_operation(lk_view *view, enum lk_cursor_mode mode, uint32_t edges);
void view_request_move(struct wl_listener *listener, void *data);
void view_request_resize(struct wl_listener *listener, void *data);
void view_move(lk_server *server, lk_view *view);
void view_resize(lk_server *server, lk_view *view, uint32_t edges);

#endif