#include "include/surface.hpp"

void surface_map(struct wl_listener *listener, void *data) {
    /* Called when the surface is mapped, or ready to display on-screen. */
    struct lk_view *view = wl_container_of(listener, view, map);
    view->mapped = true;
    focus_view(view, view->xdg_surface->surface);
}

void surface_unmap(struct wl_listener *listener, void *data) {
    /* Called when the surface is unmapped, and should no longer be shown. */
    struct lk_view *view = wl_container_of(listener, view, unmap);
    view->mapped = false;
}

void surface_destroy(struct wl_listener *listener, void *data) {
    /* Called when the surface is destroyed and should never be shown again. */
    struct lk_view *view = wl_container_of(listener, view, destroy);
    wl_list_remove(&view->link);
    free(view);
}

void surface_recieved(struct wl_listener *listener, void *data) {
    /* This event is raised when wlr_xdg_shell receives a new xdg surface from a
	 * client, either a toplevel (application window) or popup. */
    struct lk_server *server = wl_container_of(listener, server, new_xdg_surface);
    auto xdg_surface = (struct wlr_xdg_surface *)data;
    if (xdg_surface->role != WLR_XDG_SURFACE_ROLE_TOPLEVEL) {
        return;
    }

    /* Allocate a lk_view for this surface */
    auto view = (struct lk_view *)calloc(1, sizeof(struct lk_view));
    view->server = server;
    view->xdg_surface = xdg_surface;

    /* Listen to the various events it can emit */
    view->map.notify = surface_map;
    wl_signal_add(&xdg_surface->events.map, &view->map);
    view->unmap.notify = surface_unmap;
    wl_signal_add(&xdg_surface->events.unmap, &view->unmap);
    view->destroy.notify = surface_destroy;
    wl_signal_add(&xdg_surface->events.destroy, &view->destroy);

    /* cotd */
    struct wlr_xdg_toplevel *toplevel = xdg_surface->toplevel;
    view->request_move.notify = view_request_move;
    wl_signal_add(&toplevel->events.request_move, &view->request_move);
    view->request_resize.notify = view_request_resize;
    wl_signal_add(&toplevel->events.request_resize, &view->request_resize);

    /* Add it to the list of views. */
    wl_list_insert(&server->views, &view->link);
}
