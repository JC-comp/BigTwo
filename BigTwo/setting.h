#ifndef SETTING_H
#define SETTING_H

#include "game.h"
#include "option.h"

struct GameConfig
{
    long unsigned int player_count;
    long unsigned int computer_count;
    long unsigned int joker_mode;
    long unsigned int swap_mode;
};

class Setting: public Screen
{
    Q_OBJECT
    using Screen::Screen;
public:
    void show(QGraphicsScene * scene);
    GameConfig getConfig();

private:
    Option *player_num;
    Option *computer_num;
    Option *joker_mode;
    Option *swap_card_mode;

public slots:
    void checkPlayrNum();
};


#endif // SETTING_H
