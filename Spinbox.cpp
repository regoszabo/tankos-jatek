#include "spinbox.hpp"
#include "graphics.hpp"
#include <string>

using namespace genv;
using namespace std;

Spinbox::Spinbox(int x, int y, int width, int height, int min_val, int max_val)
    : Widget(x, y, width, height), _value(0), _min(min_val), _max(max_val) {}

void Spinbox::draw() {
    int button_width = 20;
    int button_height = _size_y / 2;

    gout << move_to(_x, _y) << color(0, 0, 0) << box(_size_x, _size_y);
    gout << move_to(_x + 1, _y + 1) << color(255, 255, 255) << box(_size_x - 2, _size_y - 2);

    string sz = to_string(_value);
    gout << move_to(_x + 10, _y + (_size_y / 2 + gout.cascent() / 2) - 2) << color(0, 0, 0);
    for (char c : sz) {
        gout << text(string(1, c));
    }

    gout << move_to(_x + _size_x - button_width, _y) << color(0, 0, 0) << box(button_width, button_height);
    gout << move_to(_x + _size_x - button_width + 1, _y + 1) << color(160, 160, 160) << box(button_width - 2, button_height - 2);

    gout << move_to(_x + _size_x - button_width, _y + button_height) << color(0, 0, 0) << box(button_width, button_height);
    gout << move_to(_x + _size_x - button_width + 1, _y + button_height + 1) << color(160, 160, 160) << box(button_width - 2, button_height - 2);

    int button_x = _x + _size_x - button_width;
    int center_x = button_x + button_width / 2;
    int center_y_up = _y + button_height / 2;
    int center_y_down = _y + button_height + button_height / 2;

    int margin = 3;
    gout << color(0, 0, 0);
    gout << move_to(button_x + margin, center_y_up) << line(button_width - 2 * margin, 0);
    gout << move_to(center_x, _y + margin) << line(0, button_height - 2 * margin);
    gout << move_to(button_x + margin, center_y_down) << line(button_width - 2 * margin, 0);
}

void Spinbox::handle(event ev) {
    int button_width = 20;
    int button_height = _size_y / 2;

    if (ev.type == ev_mouse && ev.button == btn_left) {
        if (ev.pos_x >= _x + _size_x - button_width && ev.pos_x <= _x + _size_x &&
            ev.pos_y >= _y && ev.pos_y <= _y + button_height) {
            if (_value < _max) _value++;
        } else if (ev.pos_x >= _x + _size_x - button_width && ev.pos_x <= _x + _size_x &&
                   ev.pos_y >= _y + button_height && ev.pos_y <= _y + 2 * button_height) {
            if (_value > _min) _value--;
        }
    }

    if (ev.type == ev_key) {
        if (ev.keycode == key_up && _value < _max) _value++;
        if (ev.keycode == key_pgup && _value + 10 <= _max) _value += 10;
        if (ev.keycode == key_pgup && _value + 10 > _max) _value = _max;
        if (ev.keycode == key_down && _value > _min) _value--;
        if (ev.keycode == key_pgdn && _value - 10 >= _min) _value -= 10;
        if (ev.keycode == key_pgdn && _value - 10 < _min) _value = _min;
    }
}

int Spinbox::getValue() const {
    return _value;
}
