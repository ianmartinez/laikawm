#ifndef LK_PANEL_H
#define LK_PANEL_H

#include "widget.hpp"
#include <vector>
#include <memory>

/**
 * A widget that has child widgets.
 */
class lk_panel : public lk_widget {
    public:
        std::vector<std::unique_ptr<lk_widget>> children;
        
};

#endif
