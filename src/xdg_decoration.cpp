#include "include/xdg_decoration.hpp"
#include <wayland-util.h>

lk_server_decoration::~lk_server_decoration() {
    wl_list_remove(&this->destroy.link);
    wl_list_remove(&this->mode.link);
}
