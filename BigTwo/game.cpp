#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QDebug>
#include <qmediaplaylist.h>

#include "game.h"
#include "welcome.h"
#include "setting.h"
#include "play.h"

Game::Game(): QGraphicsView(){
    // create a scene
    scene = new QGraphicsScene(this);
    currentScreen = nullptr;
    // set the scene
    setScene(scene);

    // alter window
    scene->setSceneRect(0,0,1080,960);
    setFixedSize(scene->width() + 10, scene->height() + 10);

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/music/Dataset/Sound/little-adventure-95822.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer* mediaPlayer = new QMediaPlayer;
    mediaPlayer->setPlaylist(playlist);
    mediaPlayer->setVolume(30);
    mediaPlayer->play();
    if(clickPlayer == nullptr) {
        clickPlayer = new QMediaPlayer;
        clickPlayer->setMedia(QUrl("qrc:/music/Dataset/Sound/click.mp3"));
    }
}
QMediaPlayer* Game::clickPlayer = 0;

void Game::click() {
    if(clickPlayer->state() == QMediaPlayer::PlayingState)
        clickPlayer->setPosition(0);
    else
        clickPlayer->play();
}

void Game::displayMainMenu(){
    clear();
    currentScreen = new Welcome(this);
    currentScreen->show(scene);
}


void Game::setting(){
    // initialize

    // clear the screen
    clear();
    currentScreen = new Setting(this);
    currentScreen->show(scene);
}

void Game::start(){
    // initialize

    // clear the screen
    GameConfig config = ((Setting*)currentScreen)->getConfig();
    clear();
    currentScreen = new Play(this);
    ((Play*)currentScreen)->show(scene, config);
}

void Game::clear() {
    if(currentScreen != nullptr)
        delete currentScreen;
    //setBackgroundBrush(QBrush(Qt::NoBrush));
    scene->clear();
}
Game::~Game()
{
    delete currentScreen;
}

Screen::Screen(Game *game): _game(game)
{
}

void Screen::show(QGraphicsScene * scene) {

}
