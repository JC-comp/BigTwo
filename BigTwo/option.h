#ifndef OPTION_H
#define OPTION_H

#include <QObject>
#include <QGraphicsItemGroup>
class Option : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    Option(QString name, std::initializer_list<QString> values);
    void setValue(long unsigned int position);
    long unsigned int getValue();
private:
    QGraphicsTextItem* value;
    QString *_values;
    size_t value_size;
    long unsigned int value_position;

signals:
    void changed();

public slots:
    void back();
    void forward();
};

class ActionButton : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
    ActionButton(const QPolygonF &polygon,
                 QGraphicsPolygonItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked();
};

#endif // OPTION_H
