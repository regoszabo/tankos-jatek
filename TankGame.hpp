#ifndef TANKGAME_HPP
#define TANKGAME_HPP

#include "Tank.hpp"
#include "Terrain.hpp"
#include "Bullet.hpp"
#include "ExplosionAnimation.hpp"
#include "Spinbox.hpp"
#include "Statictext.hpp"
#include "Button.hpp"
#include "JatekMester.hpp"
#include "graphics.hpp"

enum Allapot { KEZDO, JATEK, VEGE };

class TankGame {
private:
    Allapot allapot;
    genv::canvas hatter, startgomb;
    int hatter_width, hatter_height;
    int startgomb_width, startgomb_height;

    Terrain* terrain;
    Tank* tank1;
    Tank* tank2;
    JatekMester jatekMester;

    Spinbox* spin_szog;
    Spinbox* spin_ero;
    Statictext* szog_label;
    Statictext* ero_label;
    Statictext* szel_kijelzo;
    Statictext* eletek1;
    Statictext* eletek2;
    Statictext* info_szoveg;
    Button* ujra_gomb;
    Button* start_gomb_widget;

    void betolt_kepek();
    void kezdo_kepernyo(const genv::event& ev);
    void jatek_init();
    void jatek_fut(const genv::event& ev);
    void jatek_vege_kezeles(const genv::event& ev);
    void eletek_frissit();
    void szel_frissit_szoveg();

public:
    TankGame();
    void futtat();
};

#endif
