#include "KepBetolto.hpp"
#include <fstream>
#include <stdexcept>

genv::canvas load_kep_to_canvas(const std::string& filename, int& w, int& h) {
    std::ifstream f(filename);
    if (!f) throw std::runtime_error("Nem sikerült megnyitni: " + filename);

    f >> w >> h;
    genv::canvas c;
    c.open(w, h);

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int r, g, b;
            f >> r >> g >> b;
            c << genv::move_to(x, y) << genv::color(r, g, b) << genv::dot;
        }
    }

    return c;
}
