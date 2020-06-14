#ifndef LK_XWAYLAND_EVENTS_H
#define LK_XWAYLAND_EVENTS_H

#include "../wl_includes.hpp"
#include "../xwayland/xwayland.hpp"
#include <wayland-server-core.h>
#include <xcb/xcb.h>

void xwayland_ready(struct wl_listener *listener, void *data);
void xwayland_surface_added(struct wl_listener *listener, void *data);
void xwayland_surface_destroy(struct wl_listener *listener, void *data);
void xwayland_surface_request_configure(struct wl_listener *listener, void *data);
void xwayland_surface_request_fullscreen(struct wl_listener *listener, void *data);
void xwayland_surface_request_activate(struct wl_listener *listener, void *data);
void xwayland_surface_request_move(struct wl_listener *listener, void *data);
void xwayland_surface_request_resize(struct wl_listener *listener, void *data);
void xwayland_surface_set_title(struct wl_listener *listener, void *data);
void xwayland_surface_set_class(struct wl_listener *listener, void *data);
void xwayland_surface_set_role(struct wl_listener *listener, void *data);
void xwayland_surface_set_window_type(struct wl_listener *listener, void *data);
void xwayland_surface_set_hints(struct wl_listener *listener, void *data);
void xwayland_surface_set_decorations(struct wl_listener *listener, void *data);
void xwayland_view_unmap(struct wl_listener *listener, void *data);
void xwayland_view_map(struct wl_listener *listener, void *data);

// Unmanaged xwayland view

void unmanaged_view_request_configure(struct wl_listener *listener, void *data);
void unmanaged_view_map(struct wl_listener *listener, void *data);
void unmanaged_view_unmap(struct wl_listener *listener, void *data);
void unmanaged_view_destroy(struct wl_listener *listener, void *data);
void unmanaged_view_commit(struct wl_listener *listener, void *data);

#endif
