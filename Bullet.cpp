#include "Bullet.hpp"
#include "graphics.hpp"
#include <cmath>

using namespace genv;
using namespace std;

Bullet::Bullet(const Tank& tank, int szog, int ero, int szel_ero, int szel_irany) {
    float rad = szog * M_PI / 180.0;
    int tx = tank.get_x() + 25;
    int ty = tank.get_y();
    x = tx;
    y = ty;
    int irany = tank.is_balrol() ? 1 : -1;
    vx = cos(rad) * ero * irany + szel_ero * 0.5;
    vy = -sin(rad) * ero;

    utvonal.emplace_back((int)x, (int)y); // elsõ pont
}

void Bullet::update() {
    x += vx;
    y += vy;
    vy += gravity;
    vx *= (1.0f - drag);

    utvonal.emplace_back((int)x, (int)y); // pont hozzáadása
}

void Bullet::draw() const {
    if (utvonal.empty()) return;

    gout << color(255, 255, 0); // sárga röppálya

    // összekötjük a pontokat
    auto prev = utvonal[0];
    for (size_t i = 1; i < utvonal.size(); ++i) {
        auto curr = utvonal[i];
        gout << move_to(prev.first, prev.second) << line_to(curr.first, curr.second);
        prev = curr;
    }

    // aktuális pozíció kiemelve
    gout << move_to((int)x, (int)y) << dot;
}

int Bullet::get_x() const { return static_cast<int>(x); }
int Bullet::get_y() const { return static_cast<int>(y); }
