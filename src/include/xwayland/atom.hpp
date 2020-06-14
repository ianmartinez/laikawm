#ifndef LK_ATOM_H
#define LK_ATOM_H

struct lk_xwayland_atom {
    const int8_t type;
    const char *name;
};

inline bool operator==(const lk_xwayland_atom &lhs, const lk_xwayland_atom &rhs) {
    return lhs.type == rhs.type;
}

inline bool operator!=(const lk_xwayland_atom &lhs, const lk_xwayland_atom &rhs) {
    return !(lhs == rhs);
}

lk_xwayland_atom lk_xwayland_atom_name[] = {
    {0, "_NET_WM_WINDOW_TYPE_NORMAL" },
    {1, "_NET_WM_WINDOW_TYPE_DIALOG" },
    {2, "_NET_WM_WINDOW_TYPE_UTILITY" },
    {3, "_NET_WM_WINDOW_TYPE_TOOLBAR" },    
    {4, "_NET_WM_WINDOW_TYPE_SPLASH" },
    {5, "_NET_WM_WINDOW_TYPE_MENU" },
    {6, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU" },
    {7, "_NET_WM_WINDOW_TYPE_POPUP_MENU" },
    {8, "_NET_WM_WINDOW_TYPE_TOOLTIP" },
    {9, "_NET_WM_WINDOW_TYPE_NOTIFICATION" },
    {10, "_NET_WM_STATE_MODAL" }
};
#endif
