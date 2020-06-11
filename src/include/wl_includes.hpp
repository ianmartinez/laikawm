#ifndef WL_INCLUDES_H
#define WL_INCLUDES_H

/**
 * Wrap the wlroots includes in a
 * C++ compatible header file.
 */

#include <math.h>
// Make the compiler shut up about keywords
// that aren't keywords in C but are in C++
#define class class_
#define namespace namespace_
#define static

extern "C" {
#include <wlr/backend.h>
#include <wlr/render/wlr_renderer.h>
#include <wlr/types/wlr_compositor.h>
#include <wlr/types/wlr_cursor.h>
#include <wlr/types/wlr_data_device.h>
#include <wlr/types/wlr_input_device.h>
#include <wlr/types/wlr_keyboard.h>
#include <wlr/types/wlr_layer_shell_v1.h>
#include <wlr/types/wlr_matrix.h>
#include <wlr/types/wlr_output.h>
#include <wlr/types/wlr_output_layout.h>
#include <wlr/types/wlr_seat.h>
#include <wlr/types/wlr_xcursor_manager.h>
#include <wlr/types/wlr_xdg_shell.h>
#include <wlr/util/log.h>

#include "wlr-layer-shell-unstable-v1-protocol.h"
#include "xdg-decoration-unstable-v1-protocol.h"
}

#undef static
#undef class
#undef namespace

#endif
