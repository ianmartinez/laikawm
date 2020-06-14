#include "../include/events/xwayland_events.hpp"
#include "../include/xwayland/xwayland_view.hpp"
#include <server.hpp>

void xwayland_ready(struct wl_listener *listener, void *data) {
    wlr_log(WLR_INFO, "Xwayland is running.");
    lk_server *server =
        wl_container_of(listener, server, xwayland_ready);
    lk_xwayland xwayland = server->xwayland;

    xcb_connection_t *xcb_conn = xcb_connect(NULL, NULL);
    int xcb_connect_error = xcb_connection_has_error(xcb_conn);
    if (xcb_connect_error) {
        wlr_log(WLR_ERROR, "XCB connect failed: %d", xcb_connect_error);
        return;
    }

    xcb_intern_atom_cookie_t cookies[ATOM_LAST];
    for (size_t i = 0; i < ATOM_LAST; i++) {
        cookies[i] =
            xcb_intern_atom(xcb_conn, 0, strlen(atom_map[i]), atom_map[i]);
    }

    for (size_t i = 0; i < ATOM_LAST; i++) {
        xcb_generic_error_t *atom_reply_error = NULL;
        auto atom_reply = xcb_intern_atom_reply(xcb_conn, cookies[i], &atom_reply_error);

        if (atom_reply != NULL && atom_reply_error == NULL) {
            xwayland.atoms[i] = atom_reply->atom;
        }

        free(atom_reply);

        if (atom_reply_error != NULL) {
            wlr_log(WLR_ERROR, "Error with atom %s, X11 error code %d",
                    atom_map[i], atom_reply_error->error_code);
            free(atom_reply_error);
            break;
        }
    }

    xcb_disconnect(xcb_conn);
}

void xwayland_surface_added(struct wl_listener *listener, void *data) {
    wlr_log(WLR_INFO, "Recieved Xwayland surface");
    auto xsurface = (struct wlr_xwayland_surface *)data;

    if (xsurface->override_redirect) {
        wlr_log(WLR_DEBUG, "New xwayland unmanaged surface");

        /**
         * TODO: Create an unmanaged "surface"
         * that doesn't have all the event handlers
         * a managed one does.
         */
        //create_unmanaged(xsurface);

        return;
    }

    wlr_log(WLR_DEBUG, "New xwayland surface title='%s'",
            xsurface->title);

    lk_xwayland_view *xw_view = new lk_xwayland_view();
    xw_view->wlr_xwayland_surface = xsurface;

    // Surface destroy event
    wl_signal_add(&xsurface->events.destroy, &xw_view->destroy);
    xw_view->destroy.notify = xwayland_surface_destroy;

    // Surface request configure event
    wl_signal_add(&xsurface->events.request_configure, &xw_view->request_configure);
    xw_view->request_configure.notify = xwayland_surface_request_configure;

    wl_signal_add(&xsurface->events.request_fullscreen, &xw_view->request_fullscreen);
    xw_view->request_fullscreen.notify = xwayland_surface_request_fullscreen;

    wl_signal_add(&xsurface->events.request_activate, &xw_view->request_activate);
    xw_view->request_activate.notify = xwayland_surface_request_activate;

    wl_signal_add(&xsurface->events.request_move, &xw_view->request_move);
    xw_view->request_move.notify = xwayland_surface_request_move;

    wl_signal_add(&xsurface->events.request_resize, &xw_view->request_resize);
    xw_view->request_resize.notify = xwayland_surface_request_resize;

    wl_signal_add(&xsurface->events.set_title, &xw_view->set_title);
    xw_view->set_title.notify = xwayland_surface_set_title;

    wl_signal_add(&xsurface->events.set_class, &xw_view->set_class);
    xw_view->set_class.notify = xwayland_surface_set_class;

    wl_signal_add(&xsurface->events.set_role, &xw_view->set_role);
    xw_view->set_role.notify = xwayland_surface_set_role;

    wl_signal_add(&xsurface->events.set_window_type, &xw_view->set_window_type);
    xw_view->set_window_type.notify = xwayland_surface_set_window_type;

    wl_signal_add(&xsurface->events.set_hints, &xw_view->set_hints);
    xw_view->set_hints.notify = xwayland_surface_set_hints;

    wl_signal_add(&xsurface->events.set_decorations, &xw_view->set_decorations);
    xw_view->set_decorations.notify = xwayland_surface_set_decorations;

    wl_signal_add(&xsurface->events.unmap, &xw_view->unmap);
    xw_view->unmap.notify = xwayland_view_unmap;

    wl_signal_add(&xsurface->events.map, &xw_view->map);
    xw_view->map.notify = xwayland_view_map;

    xsurface->data = xw_view;
}


void xwayland_surface_destroy(struct wl_listener *listener, void *data) {    
	lk_xwayland_view *xw_view =
		wl_container_of(listener, xw_view, destroy);
    wlr_log(WLR_INFO, "Destroying Xwayland view.");
}

void xwayland_surface_request_configure(struct wl_listener *listener, void *data) {    
	lk_xwayland_view *xw_view =
		wl_container_of(listener, xw_view, request_configure);
    wlr_log(WLR_INFO, "Xwayland view requested configure.");
}

void xwayland_surface_request_fullscreen(struct wl_listener *listener, void *data) {    
	lk_xwayland_view *xw_view =
		wl_container_of(listener, xw_view, request_fullscreen);
    wlr_log(WLR_INFO, "Xwayland view requested fullscreen.");
}

void xwayland_surface_request_activate(struct wl_listener *listener, void *data) {    
	lk_xwayland_view *xw_view =
		wl_container_of(listener, xw_view, request_activate);
    wlr_log(WLR_INFO, "Xwayland view requested activate.");
}

void xwayland_surface_request_move(struct wl_listener *listener, void *data) {    
	lk_xwayland_view *xw_view =
		wl_container_of(listener, xw_view, request_move);
    wlr_log(WLR_INFO, "Xwayland view requested move.");
}

void xwayland_surface_request_resize(struct wl_listener *listener, void *data) {    
	lk_xwayland_view *xw_view =
		wl_container_of(listener, xw_view, request_resize);
    wlr_log(WLR_INFO, "Xwayland view requested resize.");
}

void xwayland_surface_set_title(struct wl_listener *listener, void *data) {    
	lk_xwayland_view *xw_view =
		wl_container_of(listener, xw_view, set_title);
    wlr_log(WLR_INFO, "Xwayland view set title.");
}

void xwayland_surface_set_class(struct wl_listener *listener, void *data) {    
	lk_xwayland_view *xw_view =
		wl_container_of(listener, xw_view, set_class);
    wlr_log(WLR_INFO, "Xwayland view set class.");
}

void xwayland_surface_set_role(struct wl_listener *listener, void *data) {    
	lk_xwayland_view *xw_view =
		wl_container_of(listener, xw_view, set_role);
    wlr_log(WLR_INFO, "Xwayland view set role.");
}

void xwayland_surface_set_window_type(struct wl_listener *listener, void *data) {    
	lk_xwayland_view *xw_view =
		wl_container_of(listener, xw_view, set_window_type);
    wlr_log(WLR_INFO, "Xwayland view window type.");
}

void xwayland_surface_set_hints(struct wl_listener *listener, void *data) {    
	lk_xwayland_view *xw_view =
		wl_container_of(listener, xw_view, set_hints);
    wlr_log(WLR_INFO, "Xwayland view set hints.");
}

void xwayland_surface_set_decorations(struct wl_listener *listener, void *data) {    
	lk_xwayland_view *xw_view =
		wl_container_of(listener, xw_view, set_decorations);
    wlr_log(WLR_INFO, "Xwayland view set decorations.");
}

void xwayland_view_map(struct wl_listener *listener, void *data) {    
	lk_xwayland_view *xw_view =
		wl_container_of(listener, xw_view, map);
    wlr_log(WLR_INFO, "Map Xwayland view ");
}

void xwayland_view_unmap(struct wl_listener *listener, void *data) {    
	lk_xwayland_view *xw_view =
		wl_container_of(listener, xw_view, unmap);
    wlr_log(WLR_INFO, "Unmap Xwayland view.");
}
