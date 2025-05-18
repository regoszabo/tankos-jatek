#include "Tank.hpp"
#include "KepBetolto.hpp"

using namespace genv;
using namespace std;

Tank::Tank(const string& test_fajl, int x, int terrain_y, bool balrol_)
    : Widget(x, 0, 0, 0), szog(0), hp(3), balrol(balrol_) {
    kep = load_kep_to_canvas(test_fajl, _size_x, _size_y);
    _x = x;
    _y = terrain_y - _size_y;
}

void Tank::draw() {
    gout << stamp(kep, _x, _y);
}

void Tank::set_szog(int s) { szog = s; }
int Tank::get_szog() const { return szog; }
void Tank::set_hp(int e) { hp = e; }
int Tank::get_hp() const { return hp; }
void Tank::damage() { if (hp > 0) --hp; }
int Tank::get_x() const { return _x; }
int Tank::get_y() const { return _y; }
bool Tank::is_balrol() const { return balrol; }

bool Tank::hit(int x, int y) const {
    return x >= _x && x <= _x + _size_x &&
           y >= _y && y <= _y + _size_y;
}
