#ifndef PLAY_H
#define PLAY_H

#include "setting.h"
#include "engine.h"
#include "cardpixmapitem.h"

class Play : public Screen
{
    Q_OBJECT
    using Screen::Screen;
    using Screen::show;
public:
    ~Play();
    void show(QGraphicsScene * scene, GameConfig config);
    void deSelectAll();
private:
    QGraphicsScene* _scene;
    Engine* engine;
    void update_screen();
    void winner_screen();
    QGraphicsTextItem* countDownText;
    std::vector<CardPixmapItem*> cardsToPlay;
    int traverseCount;
    CombinationType traverseType;
    Combination* selecedCombination;
    void traverse(CombinationType type);
    QMediaPlayer* winPlayer;

public slots:
    void loop();
    void newRound();
    void play();
    void pass();
    void traversePair();
    void traverseStraight();
    void traverseFull();
    void traverseFour();
    void traverseFlush();
    void cardClicked(CardPixmapItem* , int);
};

#endif // PLAY_H
