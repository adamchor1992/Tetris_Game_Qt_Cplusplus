#ifndef DRAWER_H
#define DRAWER_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QPen>
#include <QBrush>
#include <QVector>
#include <QColor>
#include <placedblocks.h>

class Drawer : public QObject
{
    Q_OBJECT
public:
    explicit Drawer(QGraphicsScene *_scene, QObject *parent = nullptr);

    bool checkCoordinatesValidity(int x, int y);
    bool checkCoordinatesValidity(QVector<int> block_coordinates);
    void paintSquare(int x, int y, QBrush brush);
    void paintPlacedBlocks(const PlacedBlocks *placedblocks);
    QVector<QGraphicsRectItem*> paintBlock(QVector<int> block_coordinates, QColor random_color);
    void deleteSquare(int x, int y);
    void deleteBlock(QVector<int> block_coordinates);
    void deleteBlock(QVector<QGraphicsRectItem*> block_rect_graphic_pointers);

private:
    QGraphicsScene *scene;
    int square_size;
    QPen red_pen;
    QBrush red_brush;
    QPen black_pen;
    QBrush black_brush;

signals:

public slots:
};

#endif // DRAWER_H
