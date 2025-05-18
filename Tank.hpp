#ifndef TANK_HPP
#define TANK_HPP

#include "graphics.hpp"
#include "widgets.hpp"
#include <string>

class Tank : public Widget {
private:
    genv::canvas kep;
    int szelesseg, magassag;
    int szog;
    int hp;
    bool balrol;

public:
    Tank(const std::string& test_fajl, int x, int terrain_y, bool balrol_);
    void draw() override;
    void handle(genv::event) override {}  // nem interaktív
    bool is_selected(int, int) override { return false; }

    void set_szog(int s);
    int get_szog() const;
    void set_hp(int e);
    int get_hp() const;
    void damage();

    int get_x() const;
    int get_y() const;
    bool is_balrol() const;
    bool hit(int x, int y) const;
};

#endif
