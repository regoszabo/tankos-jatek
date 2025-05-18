#ifndef JATEKMESTER_HPP
#define JATEKMESTER_HPP

#include "Tank.hpp"
#include "Terrain.hpp"
#include "Bullet.hpp"
#include "ExplosionAnimation.hpp"

class JatekMester {
private:
    Terrain* terrain;
    Tank* tank1;
    Tank* tank2;
    Bullet* bullet;
    ExplosionAnimation* explosion;

    int aktiv_jatekos;
    int szel_ero;
    int szel_irany;

public:
    JatekMester();
    void ujraindit();

    void init(Terrain* t, Tank* t1, Tank* t2);
    void loves_indit(Tank* lo, int szog, int ero);
    void frissit_allapot();
    void robbanas(int x, int y);

    Bullet* get_bullet() const;
    ExplosionAnimation* get_explosion() const;
    int get_szel_ero() const;
    int get_szel_irany() const;
    int get_aktiv_jatekos() const;
    void frissit_szel();
    bool vege() const;
};

#endif
