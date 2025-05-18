#include "Terrain.hpp"
#include "graphics.hpp"
#include <cmath>

using namespace genv;

Terrain::Terrain(int w, int h) : Widget(0, 0, w, h) {
    for (int x = 0; x < _size_x; ++x) {
        int y = _size_y - 80 - 40 * std::sin(x * 0.01);
        felszin.push_back(y);
    }
}

void Terrain::draw() {
    for (int x = 0; x < _size_x; ++x) {
        int y = felszin[x];
        for (int j = y; j < _size_y; ++j) {
            gout << move_to(x, j) << color(0, 160, 0) << dot;
        }
    }
}

bool Terrain::check_collision(int x, int y) const {
    return x >= 0 && x < _size_x && y >= felszin[x];
}

int Terrain::get_height(int x) const {
    if (x >= 0 && x < _size_x) return felszin[x];
    return _size_y;
}

int Terrain::get_width() const { return _size_x; }
int Terrain::get_height() const { return _size_y; }
