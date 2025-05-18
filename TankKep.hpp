
#ifndef TANKKEP_HPP
#define TANKKEP_HPP

#include "graphics.hpp"
#include <string>
#include <vector>

struct RGB {
    int r, g, b;
};

class TankKep {
public:
    TankKep(const std::string& fajlnev);

    int szelesseg() const;
    int magassag() const;

    void kirajzol_forgatva(genv::canvas& cel, int x_eltol, int y_eltol, double szog_fok) const;

private:
    std::vector<std::vector<RGB>> pixelek;
    int szel, mag;
};

#endif
