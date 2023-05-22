#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QMediaPlayer>

class Game;

class Screen: public QObject
{
    Q_OBJECT
public:
    Screen(Game *game);
    virtual void show(QGraphicsScene * scene);

protected:
    Game* _game;
};

class Game: public QGraphicsView {
    Q_OBJECT
public:
    // member functions
    Game();
    ~Game();

    // member attributes
    static void click();

public slots:
    void displayMainMenu();
    void setting();
    void start();

private:
    QGraphicsScene * scene;
    void clear();
    Screen* currentScreen;
    static QMediaPlayer* clickPlayer;
};

#endif // GAME_H
