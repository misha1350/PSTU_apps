#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QMainWindow>
#include <QtCore>
#include <QQueue>
#include <QtGui>
#include <QMessageBox>

#include <QPainter>
#include <QGraphicsScene>
#include "paint.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Graphics; }
QT_END_NAMESPACE

class Graphics : public QMainWindow
{
    Q_OBJECT

public:
    Graphics(QWidget *parent = nullptr);
    ~Graphics();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Graphics *ui;
    QGraphicsScene *scene;
    MyPoint *draw;
    QGraphicsEllipseItem *circle;
    QGraphicsLineItem *line;
    QGraphicsPathItem *path;
};

#endif // GRAPHICS_H
