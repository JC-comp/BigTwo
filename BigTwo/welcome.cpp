#include <QBrush>
#include <QImage>
#include "welcome.h"
#include "button.h"

void Welcome::show(QGraphicsScene * scene) {
    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Big Two Game"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    titleText->setDefaultTextColor(Qt::white);
    int txPos = _game->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    Button* playButton = new Button(QString("Play"));
    int bxPos = _game->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275 + 150;
    playButton->setPos(bxPos,byPos);
    QObject::connect(playButton,SIGNAL(clicked()),_game,SLOT(setting()));
    scene->addItem(playButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = _game->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350 + 160;
    quitButton->setPos(qxPos,qyPos);
    QObject::connect(quitButton,SIGNAL(clicked()),_game,SLOT(close()));
    scene->addItem(quitButton);

    // setbackground
    QImage backgroundImage(":/images/Dataset/Image/menu_bg.jpg");
    QBrush backgroundBrush(backgroundImage.scaled(_game->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    _game->setBackgroundBrush(backgroundBrush);
}
