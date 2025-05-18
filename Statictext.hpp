#ifndef STATICTEXT_HPP
#define STATICTEXT_HPP

#include "graphics.hpp"
#include <string>

class Statictext {
public:
    Statictext(int x, int y, const std::string& text);

    void set_text(const std::string& new_text);
    void draw() const;

private:
    int x, y;
    std::string text;
};

#endif
