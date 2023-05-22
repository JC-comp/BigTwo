#include "cardpixmapitem.h"

CardPixmapItem::CardPixmapItem(const QPixmap &pixmap, Card card, size_t position, QGraphicsItem *parent)
    :QGraphicsPixmapItem(pixmap, parent), _card(card), _position(position)
{
    _selected = 0;
}


void CardPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setSelected(!_selected);
    emit clicked(this, _selected);
}

void CardPixmapItem::setSelected(int selected)
{
    _selected = selected;
    if(_selected) {
        QTransform transform;
        transform.translate(0, -10);  // Translates by 50 units along the Y-axis
        setTransform(transform);
    } else {
        setTransform(QTransform());
    }
}
