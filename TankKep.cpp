
#include "TankKep.hpp"
#include <fstream>
#include <cmath>
#include <stdexcept>

using namespace std;
using namespace genv;

TankKep::TankKep(const string& fajlnev) {
    ifstream f(fajlnev);
    if (!f) throw runtime_error("Nem sikerult megnyitni: " + fajlnev);
    f >> szel >> mag;
    pixelek.resize(mag, vector<RGB>(szel));
    for (int y = 0; y < mag; ++y) {
        for (int x = 0; x < szel; ++x) {
            int r, g, b;
            f >> r >> g >> b;
            pixelek[y][x] = {r, g, b};
        }
    }
}

int TankKep::szelesseg() const {
    return szel;
}

int TankKep::magassag() const {
    return mag;
}

void TankKep::kirajzol_forgatva(canvas& cel, int x_eltol, int y_eltol, double szog_fok) const {
    double szog_rad = szog_fok * M_PI / 180.0;
    int cx = szel / 2;
    int cy = mag / 2;

    for (int y = 0; y < mag; ++y) {
        for (int x = 0; x < szel; ++x) {
            RGB szin = pixelek[y][x];
            if (szin.r == 0 && szin.g == 0 && szin.b == 0) continue;

            int dx = x - cx;
            int dy = y - cy;
            int rx = round(dx * cos(szog_rad) - dy * sin(szog_rad));
            int ry = round(dx * sin(szog_rad) + dy * cos(szog_rad));

            int celx = x_eltol + cx + rx;
            int cely = y_eltol + cy + ry;

            cel << move_to(celx, cely) << color(szin.r, szin.g, szin.b) << dot;
        }
    }
}
