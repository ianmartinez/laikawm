#include "view.hpp"

#include <list>

bool lk_view::exists_at(double lx, double ly, struct wlr_surface **surface,
						double *sx, double *sy) {
	/*
	 * XDG toplevels may have nested surfaces, such as popup windows for context
	 * menus or tooltips. This function tests if any of those are underneath the
	 * coordinates lx and ly (in output Layout Coordinates). If so, it sets the
	 * surface pointer to that wlr_surface and the sx and sy coordinates to the
	 * coordinates relative to that surface's top-left corner.
	 */
	double view_sx = lx - this->x;
	double view_sy = ly - this->y;

	double _sx, _sy;
	struct wlr_surface *_surface = NULL;
	_surface =
		wlr_xdg_surface_surface_at(this->xdg_surface, view_sx, view_sy, &_sx, &_sy);

	if (_surface != NULL) {
		*sx = _sx;
		*sy = _sy;
		*surface = _surface;
		return true;
	}

	return false;
}

void lk_view::focus(struct wlr_surface *surface) {
	/* Note: this function only deals with keyboard focus. */
	lk_server *server = this->server;
	struct wlr_seat *seat = server->seat;
	struct wlr_surface *prev_surface = seat->keyboard_state.focused_surface;

	if (prev_surface == surface) {
		/* Don't re-focus an already focused surface. */
		return;
	}

	if (prev_surface) {
		/*
		 * Deactivate the previously focused surface. This lets the client know
		 * it no longer has focus and the client will repaint accordingly, e.g.
		 * stop displaying a caret.
		 */
		struct wlr_xdg_surface *previous =
			wlr_xdg_surface_from_wlr_surface(seat->keyboard_state.focused_surface);
		wlr_xdg_toplevel_set_activated(previous, false);
	}

	struct wlr_keyboard *keyboard = wlr_seat_get_keyboard(seat);
	/* Move the view to the front */
	this->server->views.remove(this);
	this->server->views.push_front(this);

	/* Activate the new surface */
	wlr_xdg_toplevel_set_activated(this->xdg_surface, true);

	/*
	 * Tell the seat to have the keyboard enter this surface. wlroots will keep
	 * track of this and automatically send key events to the appropriate
	 * clients without additional work on your part.
	 */
	wlr_seat_keyboard_notify_enter(seat, this->xdg_surface->surface,
								   keyboard->keycodes, keyboard->num_keycodes, &keyboard->modifiers);
}

