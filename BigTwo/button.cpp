#include "button.h"
#include "game.h"
#include <QGraphicsTextItem>
#include <QBrush>

Button::Button(QString name, QColor bgColor, QColor bgHoverColor, QGraphicsRectItem *parent)
    : QGraphicsRectItem(parent), _bgColor(bgColor), _bgHoverColor(bgHoverColor)
{
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(_bgColor);
    setBrush(brush);

    // draw the text
    text = new QGraphicsTextItem(name,this);
    text->setFont(QFont("comic sans", 15));
    text->setDefaultTextColor(Qt::white);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);

    // allow responding to hover events
    setAcceptHoverEvents(true);
}

Button::Button(QString name, QGraphicsRectItem *parent)
    :Button (name, Qt::darkRed, Qt::red, parent)
{

}



void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Game::click();
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(_bgHoverColor);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(_bgColor);
    setBrush(brush);
}
