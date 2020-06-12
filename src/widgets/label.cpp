#include "../include/widgets/label.hpp"

void lk_label::recalc_size() {
    /**
     * TODO: calculate text size.
     */
    size.width =
        padding.left + 0 + padding.right;

    size.height =
        padding.top + 0 + padding.bottom;
}

std::string lk_label::get_text() {
    return this->text;
}

void lk_label::set_text(std::string value) {
    this->text = value;
    recalc_size();
}

