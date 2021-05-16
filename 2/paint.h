#ifndef PAINT_H
#define PAINT_H

#include <QObject>
#include <QGraphicsItem>

class MyPoint : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit MyPoint(QObject *parent = 0);
    ~MyPoint();

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // PAINT_H
