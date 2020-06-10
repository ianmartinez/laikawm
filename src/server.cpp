#include "include/server.hpp"

lk_view *lk_server::view_at(double lx, double ly, struct wlr_surface **surface,
                                double *sx, double *sy) {
    /* This iterates over all of our surfaces and attempts to find one under the
	 * cursor. This relies on server->views being ordered from top-to-bottom. */

    for (auto it = views.begin(); it != views.end(); ++it) {
        lk_view *view = *it;
        if (view->exists_at(lx, ly, surface, sx, sy)) {
            return view;
        }
    }

    return NULL;
}