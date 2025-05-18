#ifndef SPINBOX_HPP_INCLUDED
#define SPINBOX_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"

class Spinbox : public Widget {
    int _value, _min, _max;
public:
    Spinbox(int x, int y, int sx, int sy, int min, int max);
    virtual void draw() override;
    virtual void handle(genv::event ev) override;
    int getValue() const;
};

#endif
