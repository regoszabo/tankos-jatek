#include "Statictext.hpp"
using namespace genv;
using namespace std;

Statictext::Statictext(int x_, int y_, const string& text_)
    : x(x_), y(y_), text(text_)
{}

void Statictext::set_text(const string& new_text) {
    text = new_text;
}

void Statictext::draw() const {
    gout << move_to(x, y) << color(255, 255, 255) << genv::text(text);
}
