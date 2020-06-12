#ifndef LK_WIDGET_H
#define LK_WIDGET_H

#include <cairo/cairo.h>
#include "sizing.hpp"

/**
 * The base class of an lk_widget.
 *
 * lk_widgets are lightweight lk_widgets
 * used internally for content on laika_wm,
 * to avoid any dependency on heavy libraries
 * such as GTK or QT.
 */
class lk_widget {
    protected:
        /**
         * Protected because all lk_widgets are
         * autosizing, so you can't manually set
         * their position and size.
         *
         * Sizes are evaluated bottom up. The child
         * widgets declare their size and then the
         * parent widget delcares its size calculated 
         * from all of its child widgets' sizes and so on...
         */
        
        /**
         * The calculated size of the widget. 
         * Updated by the virtual method recalc_size();
         */
        lk_size size;
        
        /**
         * The spacing between this widget and its 
         * children (if a content widget) or the drawn border 
         * and the other graphics (if not a content widget, 
         * such as a label).
         */
        lk_sides padding;

        /**
         * A virtual method to recalculate the widget's size.
         */
        virtual void recalc_size() = 0;
    public:        
        /**
         * The Cairo surface to draw to.
         * 
         * A widget is just a representation of
         * a region of a Cairo surface. 
         * 
         * The root widget that is the topmost 
         * parent of all of the widgets will have
         * a surface and all of its children will
         * draw to it.
         */
        cairo_t *surface;
        
        /**
         * The postion to draw this widget on the
         * Cairo surface.
         */
        lk_point position;
        
        /**
         * The padding inside of the widget
         * separating the child widgets from
         * the border of the parent.
         */
        lk_size get_size();
        void set_padding(lk_sides *value);
        lk_sides get_padding();
};

#endif

