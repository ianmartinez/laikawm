#ifndef LK_LABEL_H
#define LK_LABEL_H

#include <string>
#include "widget.hpp"


class lk_label : public lk_widget {
    protected:
        void recalc_size();

    private:
        std::string text;

    public:
        std::string  get_text();
        void set_text(std::string value);
};

#endif
