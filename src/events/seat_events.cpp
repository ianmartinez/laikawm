#include "../include/events/seat_events.hpp"

void seat_request_set_selection(struct wl_listener *listener, void *data) {
    /* This event is raised by the seat when a client wants to set the selection,
     * usually when the user copies something. wlroots allows compositors to
     * ignore such requests if they so choose, but in tinywl we always honor
     */
    lk_server *server = wl_container_of(listener, server, request_set_selection);
    auto event = (struct wlr_seat_request_set_selection_event *)data;
    wlr_seat_set_selection(server->seat, event->source, event->serial);
}
