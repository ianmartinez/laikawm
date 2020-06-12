#ifndef LK_CONTENT_WIDGET_H
#define LK_CONTENT_WIDGET_H

#include "widget.hpp"
#include <vector>
#include <memory>

/**
 * A widget that has child widgets.
 */
class content_widget : public lk_widget {
    public:
        std::vector<std::unique_ptr<lk_widget>> children;
        
};

#endif
