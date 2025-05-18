#ifndef BULLET_HPP
#define BULLET_HPP

#include "Tank.hpp"
#include <vector>

class Bullet {
public:
    Bullet(const Tank& tank, int szog, int ero, int szel_ero, int szel_irany);
    void update();
    void draw() const;
    int get_x() const;
    int get_y() const;

private:
    float x, y;
    float vx, vy;
    int gravity = 1;
    float drag = 0.01f;

    std::vector<std::pair<int, int>> utvonal; // ← új: elmentett pontok
};

#endif
