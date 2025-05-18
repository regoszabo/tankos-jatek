#include "Button.hpp"
#include "graphics.hpp"

using namespace genv;

Button::Button(int x, int y, int sx, int sy, const std::string& label_, std::function<void()> func)
    : Widget(x, y, sx, sy), label(label_), action(func) {}

void Button::draw() {
    gout << color(100, 100, 255) << move_to(_x, _y) << box(_size_x, _size_y);
    gout << color(255, 255, 255) << move_to(_x + 10, _y + _size_y / 2 + 5) << text(label);
}

void Button::handle(event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left && is_selected(ev.pos_x, ev.pos_y)) {
        if (action) action();
    }
}

bool Button::is_selected(int mx, int my) {
    return mx >= _x && mx <= _x + _size_x && my >= _y && my <= _y + _size_y;
}
