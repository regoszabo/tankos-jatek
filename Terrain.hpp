#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "widgets.hpp"
#include <vector>

class Terrain : public Widget {
public:
    Terrain(int szelesseg, int magassag);
    void draw() override;
    void handle(genv::event) override {}
    bool is_selected(int, int) override { return false; }

    bool check_collision(int x, int y) const;
    int get_height(int x) const;
    int get_width() const;
    int get_height() const;

private:
    std::vector<int> felszin;
};

#endif
