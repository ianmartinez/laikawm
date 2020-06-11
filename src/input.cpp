#include "include/input.hpp"

void server_new_input(struct wl_listener *listener, void *data) {
	/* This event is raised by the backend when a new input device becomes
	 * available. */
	lk_server *server = wl_container_of(listener, server, new_input);
	auto device = (struct wlr_input_device *)data;
	switch (device->type) {
		case WLR_INPUT_DEVICE_KEYBOARD:
			server->keyboard_added(device);
			break;
		case WLR_INPUT_DEVICE_POINTER:
			server->pointer_added(device);
			break;
		default:
			break;
	}
	
	/* We need to let the wlr_seat know what our capabilities are, which is
	 * communiciated to the client. In TinyWL we always have a cursor, even if
	 * there are no pointer devices, so we always include that capability. */
	uint32_t caps = WL_SEAT_CAPABILITY_POINTER;
    
	if (!wl_list_empty(&server->keyboards)) {
		caps |= WL_SEAT_CAPABILITY_KEYBOARD;
	}
	
	wlr_seat_set_capabilities(server->seat, caps);
}
