#ifndef LK_OUTPUT_EVENTS_H
#define LK_OUTPUT_EVENTS_H

#include "../os.hpp"

#include <stdlib.h>
#include <time.h>
#include <wayland-server-core.h>
#include <wayland-util.h>

#include "../render.hpp"
#include "../server.hpp"
#include "../wl_includes.hpp"
#include "../theme/color.hpp"

void output_add(struct wl_listener *listener, void *data);
void output_frame(struct wl_listener *listener, void *data);

#endif
