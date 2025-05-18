
#include "TankGame.hpp"
#include "KepBetolto.hpp"
#include <ctime>
#include <cstdlib>

using namespace genv;
using namespace std;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

TankGame::TankGame() : allapot(KEZDO) {
    gout.open(SCREEN_WIDTH, SCREEN_HEIGHT, true);
    gin.timer(30);

    betolt_kepek();

    spin_szog = new Spinbox(20, 60, 100, 30, 0, 70);
    spin_ero = new Spinbox(160, 60, 100, 30, 10, 100);

    szog_label = new Statictext(20, 30, "Angle:");
    ero_label = new Statictext(160, 30, "Power:");
    szel_kijelzo = new Statictext(300, 30, "Wind:");
    eletek1 = new Statictext(500, 30, "Tank1: 3 HP");
    eletek2 = new Statictext(700, 30, "Tank2: 3 HP");
    info_szoveg = new Statictext((SCREEN_WIDTH - gout.twidth("Press SPACE to shoot")) / 2, 10, "Press SPACE to shoot");

    ujra_gomb = new Button(820, 950, 240, 100, "Restart", [this]() {
        allapot = KEZDO;
    });

    start_gomb_widget = new Button(0, 0, 0, 0, "Start", [this]() {
        jatek_init();
        allapot = JATEK;
    });

    srand(time(0));
}

void TankGame::betolt_kepek() {
    hatter = load_kep_to_canvas("hatter.kep", hatter_width, hatter_height);
    startgomb = load_kep_to_canvas("startgomb.kep", startgomb_width, startgomb_height);
}

void TankGame::futtat() {
    event ev;
    while (gin >> ev) {
        if (ev.type == ev_key && ev.keycode == key_escape) return;

        gout << color(0, 0, 0) << move_to(0, 0) << box(SCREEN_WIDTH, SCREEN_HEIGHT);

        if (allapot == KEZDO) kezdo_kepernyo(ev);
        else if (allapot == JATEK) jatek_fut(ev);
        else if (allapot == VEGE) jatek_vege_kezeles(ev);

        gout << refresh;
    }
}

void TankGame::kezdo_kepernyo(const event& ev) {
    gout << stamp(hatter, 0, 0);

    int px = (SCREEN_WIDTH - startgomb_width) / 2;
    int py = (SCREEN_HEIGHT - startgomb_height) / 2;
    gout << stamp(startgomb, px, py);

    start_gomb_widget->set_position(px, py);
    start_gomb_widget->set_size(startgomb_width, startgomb_height);
    start_gomb_widget->handle(ev);
}

void TankGame::jatek_init() {
    terrain = new Terrain(SCREEN_WIDTH, SCREEN_HEIGHT);
    tank1 = new Tank("test.kep", 100, terrain->get_height(100), true);
    tank2 = new Tank("testpiros.kep", 1700, terrain->get_height(1700), false);

    jatekMester.init(terrain, tank1, tank2);
    jatekMester.ujraindit();
    szel_frissit_szoveg();
    eletek_frissit();
}

void TankGame::jatek_fut(const event& ev) {
    if (ev.type == ev_mouse && ev.button == btn_left) {
        spin_szog->set_focus(spin_szog->is_selected(ev.pos_x, ev.pos_y));
        spin_ero->set_focus(spin_ero->is_selected(ev.pos_x, ev.pos_y));
    }

    if (spin_szog->is_focused()) spin_szog->handle(ev);
    if (spin_ero->is_focused()) spin_ero->handle(ev);

    if (ev.type == ev_key && ev.keycode == key_space) {
        Tank* lo = (jatekMester.get_aktiv_jatekos() == 1 ? tank1 : tank2);
        jatekMester.loves_indit(lo, spin_szog->getValue(), spin_ero->getValue());
    }

    if (ev.type == ev_timer) {
        jatekMester.frissit_allapot();
        eletek_frissit();
        szel_frissit_szoveg();
        if (jatekMester.vege()) allapot = VEGE;
    }

    terrain->draw();
    tank1->draw();
    tank2->draw();

    szog_label->draw();
    ero_label->draw();
    spin_szog->draw();
    spin_ero->draw();
    szel_kijelzo->draw();
    eletek1->draw();
    eletek2->draw();
    gout << color(255, 255, 255)
         << move_to((SCREEN_WIDTH - gout.twidth("Press SPACE to shoot")) / 2, 20)
         << text("Press SPACE to shoot");

    if (jatekMester.get_bullet()) jatekMester.get_bullet()->draw();
    if (jatekMester.get_explosion()) jatekMester.get_explosion()->draw();

    int tx = (jatekMester.get_aktiv_jatekos() == 1 ? tank1->get_x() : tank2->get_x());
    int ty = (jatekMester.get_aktiv_jatekos() == 1 ? tank1->get_y() : tank2->get_y());

    gout << color(255, 0, 0)
         << move_to(tx + 10, ty - 15)
         << line_to(tx, ty - 5)
         << line_to(tx + 20, ty - 5)
         << line_to(tx + 10, ty - 15);


    int kozep_x = SCREEN_WIDTH / 2;
    int felszin_y = terrain->get_height(kozep_x);
    gout << color(255, 255, 255)
         << move_to(kozep_x, felszin_y)
         << line_to(kozep_x, felszin_y - 50);

    int csucs_x = kozep_x + jatekMester.get_szel_irany() * 30;
    gout << color(255, 255, 0)
         << move_to(kozep_x, felszin_y - 50)
         << line_to(csucs_x, felszin_y - 40)
         << line_to(kozep_x, felszin_y - 30)
         << line_to(kozep_x, felszin_y - 50);
}

void TankGame::jatek_vege_kezeles(const event& ev) {
    gout << stamp(hatter, 0, 0);

    int px = (SCREEN_WIDTH - startgomb_width) / 2;
    int py = (SCREEN_HEIGHT - startgomb_height) / 2;
    gout << stamp(startgomb, px, py);

    string nyertes = (tank1->get_hp() > 0 ? "Green tank wins!" : "Red tank wins!");
    gout << move_to((SCREEN_WIDTH - gout.twidth(nyertes)) / 2, 400)
         << color(255, 255, 255)
         << text(nyertes);

    start_gomb_widget->set_position(px, py);
    start_gomb_widget->set_size(startgomb_width, startgomb_height);
    start_gomb_widget->handle(ev);
}

void TankGame::eletek_frissit() {
    eletek1->set_text("Green Tank: " + to_string(tank1->get_hp()) + " HP");
    eletek2->set_text("Red Tank: " + to_string(tank2->get_hp()) + " HP");
}

void TankGame::szel_frissit_szoveg() {
    int szel_ero = jatekMester.get_szel_ero();
    szel_kijelzo->set_text("Wind: " + to_string(szel_ero));
}
