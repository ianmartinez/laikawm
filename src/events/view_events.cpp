#include "../include/events/view_events.hpp"

void view_surface_map(struct wl_listener *listener, void *data) {
    /* Called when the surface is mapped, or ready to display on-screen. */
    lk_view *view = wl_container_of(listener, view, map);

    if (view != NULL) {
        view->mapped = true;
        view->focus(view->xdg_surface->surface);
    }
}

void view_surface_unmap(struct wl_listener *listener, void *data) {
    /* Called when the surface is unmapped, and should no longer be shown. */
    lk_view *view = wl_container_of(listener, view, unmap);
    view->mapped = false;
}

void view_surface_destroy(struct wl_listener *listener, void *data) {
    /* Called when the surface is destroyed and should never be shown again. */
    lk_view *view = wl_container_of(listener, view, destroy);
    view->server->views.remove(view);
    delete view;
}

void view_surface_recieved(struct wl_listener *listener, void *data) {
    /* This event is raised when wlr_xdg_shell receives a new xdg surface from a
     * client, either a toplevel (application window) or popup. */
    lk_server *server = wl_container_of(listener, server, new_xdg_surface);
    auto xdg_surface = (struct wlr_xdg_surface *)data;
    if (xdg_surface->role != WLR_XDG_SURFACE_ROLE_TOPLEVEL) {
        return;
    }

    /* Allocate a lk_view for this surface */
    auto view = new lk_view();
    view->server = server;
    view->surface = xdg_surface->surface;
    view->xdg_surface = xdg_surface;

    /* Listen to the various events it can emit */
    view->map.notify = view_surface_map;
    wl_signal_add(&xdg_surface->events.map, &view->map);
    view->unmap.notify = view_surface_unmap;
    wl_signal_add(&xdg_surface->events.unmap, &view->unmap);
    view->destroy.notify = view_surface_destroy;
    wl_signal_add(&xdg_surface->events.destroy, &view->destroy);

    /* cotd */
    struct wlr_xdg_toplevel *toplevel = xdg_surface->toplevel;
    view->request_move.notify = view_request_move;
    wl_signal_add(&toplevel->events.request_move, &view->request_move);
    view->request_resize.notify = view_request_resize;
    wl_signal_add(&toplevel->events.request_resize, &view->request_resize);
    
    view->x = 50;
    view->y = 50;

    /* Add it to the list of views. */
    server->views.push_back(view);
}

void view_request_move(struct wl_listener *listener, void *data) {
    /* This event is raised when a client would like to begin an interactive
     * move, typically because the user clicked on their client-side
     * decorations. Note that a more sophisticated compositor should check the
     * provied serial against a list of button press serials sent to this
     * client, to prevent the client from requesting this whenever they want. */
    lk_view *view = wl_container_of(listener, view, request_move);
    view->request_cursor_operation(LK_CURSOR_MOVE, 0);
}

void view_request_resize(struct wl_listener *listener, void *data) {
    /* This event is raised when a client would like to begin an interactive
     * resize, typically because the user clicked on their client-side
     * decorations. Note that a more sophisticated compositor should check the
     * provied serial against a list of button press serials sent to this
     * client, to prevent the client from requesting this whenever they want. */
    auto event = (struct wlr_xdg_toplevel_resize_event *)data;
    lk_view *view = wl_container_of(listener, view, request_resize);
    view->request_cursor_operation(LK_CURSOR_RESIZE, event->edges);
}
