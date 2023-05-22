#include "option.h"
#include "game.h"
#include <QGraphicsRectItem>
#include <QObject>
#include <QBrush>
#include <QFont>
#include <QDebug>
#include <QGraphicsView>

Option::Option(QString name, std::initializer_list<QString> values)
    :QGraphicsItemGroup()
{
    value_size = values.size();
    _values = new QString[values.size()];
    std::copy(values.begin(), values.end(), _values);
    QFont optionFont("comic sans",18);

    // name
    QGraphicsTextItem* text = new QGraphicsTextItem(name);
    text->setDefaultTextColor(Qt::white);
    text->setFont(optionFont);
    int xPos = (200 - text->boundingRect().width())/2;
    int yPos = 50/2 - text->boundingRect().height()/2 - 12;
    text->setPos(xPos,yPos);

    // actions
    QPolygonF left_triangle;
    left_triangle << QPointF(50, 0) << QPointF(50, 50) << QPointF(0, 25);
    QPolygonF right_triangle;
    right_triangle << QPointF(50, 25) << QPointF(0, 0) << QPointF(0, 50);

    ActionButton* left = new ActionButton(left_triangle);
    ActionButton* right = new ActionButton(right_triangle);

    left->setPos(300, 0);
    right->setPos(600, 0);

    // value
    value_position = 0;
    value = new QGraphicsTextItem(_values[0]);
    xPos = (350 - value->boundingRect().width())/2 + 300;
    yPos = 0;
    value->setPos(xPos,yPos);
    value->setDefaultTextColor(Qt::white);
    value->setFont(optionFont);

    addToGroup(text);
    addToGroup(left);
    addToGroup(value);
    addToGroup(right);
    setHandlesChildEvents(false);
    setValue(0);

    QObject::connect(left,SIGNAL(clicked()),this,SLOT(back()));
    QObject::connect(right,SIGNAL(clicked()),this,SLOT(forward()));
}


void Option::back(){
    Game::click();
    value_position += value_size - 1;
    setValue(value_position);
    emit changed();
}

void Option::forward(){
    Game::click();
    value_position++;
    setValue(value_position);
}

void Option::setValue(long unsigned int position)
{
    value_position = position % value_size;
    value->setPlainText(_values[value_position]);

    int xPos = (350 - value->boundingRect().width())/2 + 300;
    int yPos = 0;
    value->setPos(xPos,yPos);

    emit changed();
}

long unsigned int Option::getValue()
{
    return value_position;
}

ActionButton::ActionButton(const QPolygonF &polygon, QGraphicsPolygonItem *parent)
 : QGraphicsPolygonItem(polygon, parent)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkRed);
    setBrush(brush);

    setAcceptHoverEvents(true);
}

void ActionButton::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}

void ActionButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
}

void ActionButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkRed);
    setBrush(brush);
}
