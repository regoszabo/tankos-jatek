#include "JatekMester.hpp"
#include <cstdlib>
#include <ctime>

JatekMester::JatekMester()
    : terrain(nullptr), tank1(nullptr), tank2(nullptr),
      bullet(nullptr), explosion(nullptr), aktiv_jatekos(1) {
    srand(time(0));
    frissit_szel();
}

void JatekMester::ujraindit() {
    bullet = nullptr;
    explosion = nullptr;
    aktiv_jatekos = 1;
    frissit_szel();
    if (tank1) tank1->set_hp(3);
    if (tank2) tank2->set_hp(3);
}

void JatekMester::init(Terrain* t, Tank* t1, Tank* t2) {
    terrain = t;
    tank1 = t1;
    tank2 = t2;
}

void JatekMester::loves_indit(Tank* lo, int szog, int ero) {
    if (!bullet && !explosion) {
        bullet = new Bullet(*lo, szog, ero, szel_ero, szel_irany);
    }
}

void JatekMester::frissit_allapot() {
    if (bullet) {
        bullet->update();
        int bx = bullet->get_x();
        int by = bullet->get_y();

        bool kifutott = bx < 0 || bx >= terrain->get_width() || by < 0 || by >= terrain->get_height();
        bool talalat = terrain->check_collision(bx, by) || tank1->hit(bx, by) || tank2->hit(bx, by);

        if (kifutott || talalat) {
            robbanas(bx, by);
            delete bullet;
            bullet = nullptr;

            if (!vege()) {
                aktiv_jatekos = 3 - aktiv_jatekos;
                frissit_szel();
            }
        }
    } else if (explosion) {
        if (explosion->done()) {
            delete explosion;
            explosion = nullptr;
        }
    }
}

void JatekMester::robbanas(int x, int y) {
    explosion = new ExplosionAnimation(x, y);
    if (tank1->hit(x, y)) tank1->damage();
    if (tank2->hit(x, y)) tank2->damage();
}

Bullet* JatekMester::get_bullet() const { return bullet; }
ExplosionAnimation* JatekMester::get_explosion() const { return explosion; }
int JatekMester::get_szel_ero() const { return szel_ero; }
int JatekMester::get_szel_irany() const { return szel_irany; }
int JatekMester::get_aktiv_jatekos() const { return aktiv_jatekos; }

void JatekMester::frissit_szel() {
    szel_ero = (rand() % 21) - 10;  // [-10, 10]
    if (szel_ero == 0) szel_irany = 0;
    else szel_irany = (szel_ero > 0 ? 1 : -1);
}

bool JatekMester::vege() const {
    return tank1->get_hp() <= 0 || tank2->get_hp() <= 0;
}
