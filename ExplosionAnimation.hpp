#ifndef EXPLOSIONANIMATION_HPP
#define EXPLOSIONANIMATION_HPP

#include "graphics.hpp"
#include <vector>
#include <tuple>

class ExplosionAnimation {
private:
    int cx, cy;
    int frame;
    int max_frames;
    int max_radius;
    std::vector<std::tuple<int, int, int>> szinek;

public:
    ExplosionAnimation(int x, int y);
    void draw();
    bool done() const;
};

#endif
