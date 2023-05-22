#ifndef CARDPIXMAPITEM_H
#define CARDPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>

#include "card.h"

class CardPixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    CardPixmapItem(const QPixmap &pixmap, Card card, size_t position, QGraphicsItem *parent = nullptr);
    int isSelected() {return _selected;}
    Card getCard() {return _card;}
    size_t getPosition() {return _position;}
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setSelected(int selected);
private:
    int _selected = 0;
    Card _card;
    size_t _position;
signals:
    void clicked(CardPixmapItem* , int);
};

#endif // CARDPIXMAPITEM_H
