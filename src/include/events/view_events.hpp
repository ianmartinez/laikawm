#ifndef LK_VIEW_EVENTS_H
#define LK_VIEW_EVENTS_H

#include <wayland-util.h>

#include "../cursor_mode.hpp"
#include "../server.hpp"
#include "../view.hpp"

void view_surface_map(struct wl_listener *listener, void *data);
void view_surface_unmap(struct wl_listener *listener, void *data);
void view_surface_destroy(struct wl_listener *listener, void *data);
void view_surface_recieved(struct wl_listener *listener, void *data);
void view_request_move(struct wl_listener *listener, void *data);
void view_request_resize(struct wl_listener *listener, void *data);

#endif
