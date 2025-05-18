#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widgets.hpp"
#include <string>
#include <functional>

class Button : public Widget {
private:
    std::string label;
    std::function<void()> action;

public:
    Button(int x, int y, int sx, int sy, const std::string& label, std::function<void()> func);

    virtual void draw() override;
    virtual void handle(genv::event ev) override;
    virtual bool is_selected(int mouse_x, int mouse_y) override;
};

#endif
