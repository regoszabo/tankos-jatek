#include "ExplosionAnimation.hpp"
#include <cmath>
using namespace genv;

ExplosionAnimation::ExplosionAnimation(int x, int y)
    : cx(x), cy(y), frame(0), max_frames(40), max_radius(50) {
    szinek = {
        {255, 200, 0},   // világos sárga
        {255, 100, 0},   // narancs
        {255, 0, 0},     // piros
        {100, 100, 100}  // szürke (füst)
    };
}

void ExplosionAnimation::draw() {
    if (frame >= max_frames) return;

    float progress = static_cast<float>(frame) / max_frames;
    int sugar = static_cast<int>(progress * max_radius);

    for (size_t i = 0; i < szinek.size(); ++i) {
        float layer_prog = 1.0f - (float)i / szinek.size();
        int layer_radius = static_cast<int>(sugar * layer_prog);
        if (layer_radius <= 0) continue;

        int r = std::get<0>(szinek[i]);
        int g = std::get<1>(szinek[i]);
        int b = std::get<2>(szinek[i]);

        for (int angle = 0; angle < 360; angle += 3) {
            int dx = layer_radius * cos(angle * M_PI / 180.0);
            int dy = layer_radius * sin(angle * M_PI / 180.0);
            gout << color(r, g, b) << move_to(cx + dx, cy + dy) << dot;
        }
    }

    ++frame;
}

bool ExplosionAnimation::done() const {
    return frame >= max_frames;
}
