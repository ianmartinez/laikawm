#include "../include/widgets/widget.hpp"

lk_size lk_widget::get_size() {
    return size;
}

void lk_widget::set_padding(lk_sides *value) {
    this->padding = *value;
    recalc_size();
}

lk_sides lk_widget::get_padding() {
    return this->padding;
}
