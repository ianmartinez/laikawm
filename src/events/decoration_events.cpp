#include "../include/events/decoration_events.hpp"
#include "../include/view.hpp"

void decoration_handle_destroy(struct wl_listener *listener, void *data) {
    auto decoration_mgr = (lk_decoration_manager *)data;
    lk_server_decoration *decoration = wl_container_of(listener, decoration, mode);
    decoration_mgr->decorations.remove(decoration);
    
    // TODO: Cleanup decoration
}

void decoration_handle_mode(struct wl_listener *listener, void *data) {
    lk_server_decoration *decoration = wl_container_of(listener, decoration, mode);
    auto decoration_surface = (struct wlr_surface *)decoration->wlr_server_decoration->surface->data;

    for (auto &view : decoration->server->views) {
        if (view->surface == decoration_surface) {
            view->client_side_decoration = WLR_SERVER_DECORATION_MANAGER_MODE_CLIENT;
        }
    }
}

void handle_decoration(struct wl_listener *listener, void *data) {
    auto wlr_decoration = (struct wlr_server_decoration *)data;
    struct lk_decoration_manager *decoration_mgr = wl_container_of(listener, decoration_mgr, server_decoration);
    lk_server_decoration *decoration = new lk_server_decoration();
    decoration->server = decoration_mgr->server;

    decoration->wlr_server_decoration = wlr_decoration;
    decoration->server = decoration_mgr->server;

    wl_signal_add(&wlr_decoration->events.destroy, &decoration->destroy);
    decoration->destroy.notify = decoration_handle_destroy;

    wl_signal_add(&wlr_decoration->events.mode, &decoration->mode);
    decoration->mode.notify = decoration_handle_mode;

    decoration_mgr->decorations.push_back(decoration);
}
