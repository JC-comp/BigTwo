#include <QBrush>
#include <QImage>
#include "setting.h"
#include "button.h"

void Setting::show(QGraphicsScene * scene) {
    // set
    player_num = new Option("Player", {"2", "3", "4"});
    computer_num = new Option("Computer", {"0", "1", "2", "3", "4"});
    joker_mode = new Option("Joker", {"off", "on"});
    swap_card_mode = new Option("Swap card", {"off", "rotate", "shuffle"});

    // create the quit button
    Button* quitButton = new Button(QString("Back"));
    Button* startButton = new Button(QString("Start"));
    QObject::connect(quitButton,SIGNAL(clicked()),_game,SLOT(displayMainMenu()));
    QObject::connect(startButton,SIGNAL(clicked()),_game,SLOT(start()));
    QObject::connect(player_num,SIGNAL(changed()),this,SLOT(checkPlayrNum()));
    QObject::connect(player_num,&Option::changed,this,&Setting::checkPlayrNum);
    QObject::connect(computer_num,&Option::changed,this,&Setting::checkPlayrNum);

    int gap = 100;
    int top = 150;
    player_num->setPos(_game->width()/2 - swap_card_mode->boundingRect().width()/2, top);
    computer_num->setPos(_game->width()/2 - swap_card_mode->boundingRect().width()/2, top + gap);
    joker_mode->setPos(_game->width()/2 - swap_card_mode->boundingRect().width()/2, top + gap * 2);
    swap_card_mode->setPos(_game->width()/2 - swap_card_mode->boundingRect().width()/2, top + gap * 3);
    quitButton->setPos(_game->width()/2 - quitButton->boundingRect().width()/2, top + gap * 4);
    startButton->setPos(_game->width()/2 - startButton->boundingRect().width()/2, top + gap * 4 + 80);


    scene->addItem(player_num);
    scene->addItem(computer_num);
    scene->addItem(joker_mode);
    scene->addItem(swap_card_mode);
    scene->addItem(quitButton);
    scene->addItem(startButton);

    // setbackground
    QImage backgroundImage(":/images/Dataset/Image/menu_bg.jpg");
    QBrush backgroundBrush(backgroundImage.scaled(_game->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    _game->setBackgroundBrush(backgroundBrush);
}

GameConfig Setting::getConfig()
{
    GameConfig config;
    config.player_count = player_num->getValue() + 2;
    config.computer_count = computer_num->getValue();
    if(config.computer_count > config.player_count)
        config.computer_count = config.player_count;
    config.joker_mode = joker_mode->getValue() == 1;
    config.swap_mode = swap_card_mode->getValue();

    return config;
}

void Setting::checkPlayrNum()
{
    if(computer_num->getValue() > player_num->getValue() + 2)
        computer_num->setValue(player_num->getValue() + 2);
}
