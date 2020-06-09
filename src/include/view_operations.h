#ifndef LK_VIEW_OPERATION_H
#define LK_VIEW_OPERATION_H

#include <wayland-util.h>

#include "cursor_mode.h"
#include "server.h"
#include "view.h"

void view_request_operation(struct lk_view *view, enum lk_cursor_mode mode, uint32_t edges);
void view_request_move(struct wl_listener *listener, void *data);
void view_request_resize(struct wl_listener *listener, void *data);
void view_move(struct lk_server *server, struct lk_view *view);
void view_resize(struct lk_server *server, struct lk_view *view, uint32_t edges);

#endif