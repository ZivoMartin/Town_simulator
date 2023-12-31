#ifndef safe_menu
#define safe_menu

#include <QTimer>
#include "../settings_building/settings.h"

class Game;

class Menu{

public:
    Menu(Game *game);
    ~Menu();
    void return_to_menu();
    void wait();
    void start_game();
    bool get_activity();
    void change_menu_info(QString lost_type);

private:
    Game *game;
    bool game_is_starting = false;
    PushButton *start_game_button;
    InfoZone *menu_info;

};


#endif