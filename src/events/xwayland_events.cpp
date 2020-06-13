#include "../include/events/xwayland_events.hpp"
#include <iostream>

void xwayland_ready(struct wl_listener *listener, void *data) {
    std::cout << "xwayland_ready!" << std::endl;
}
