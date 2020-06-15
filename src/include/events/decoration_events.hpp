#ifndef LK_DECORATION_EVENTS
#define LK_DECORATION_EVENTS

#include <wayland-server-core.h>
#include "../wl_includes.hpp"
#include "../xdg_decoration.hpp"

void decoration_handle_destroy(struct wl_listener *listener, void *data);
void decoration_handle_mode(struct wl_listener *listener, void *data);
void handle_decoration(struct wl_listener *listener, void *data);

#endif
