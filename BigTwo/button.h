#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QGraphicsRectItem>

class Button : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Button(QString name, QColor bgColor, QColor bgHovercolor, QGraphicsRectItem *parent = NULL);
    explicit Button(QString name, QGraphicsRectItem *parent = NULL);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked();
private:
    QGraphicsTextItem* text;
    QColor _bgColor, _bgHoverColor;
};

#endif // BUTTON_H
