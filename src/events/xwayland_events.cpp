#include "../include/events/xwayland_events.hpp"
void xwayland_ready(struct wl_listener *listener, void *data) {
    wlr_log(WLR_INFO, "Xwayland is running.");
}

void xwayland_new_surface(struct wl_listener *listener, void *data) {
	auto xw_surface = (struct wlr_xwayland_surface *)data;
    wlr_log(WLR_INFO, "Recieved Xwayland surface: %s", xw_surface->title);
}
