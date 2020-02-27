#pragma once

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QPen>
#include <QBrush>
#include <QVector>
#include <QColor>
#include <placed_blocks.h>

class Drawer
{
public:
    explicit Drawer(QGraphicsScene* pScene);

    bool CheckCoordinatesValidity(int x, int y);
    bool CheckCoordinatesValidity(QVector<int> blockCoordinates);
    void DrawSquare(int x, int y, QBrush brush);
    void DrawPlacedBlocks(PlacedBlocks const* p_PlacedBlocks);
    QVector<QGraphicsRectItem*> DrawBlock(QVector<int> blockCoordinates, QColor randomColor);
    void DeleteSquare(int x, int y);
    void DeleteBlock(QVector<int> blockCoordinates);
    void DeleteBlock(QVector<QGraphicsRectItem*> blockRectGraphicPointers);

private:
    QGraphicsScene* m_pScene;
    int m_SquareSize;
    QPen m_RedPen;
    QBrush m_RedBrush;
    QPen m_BlackPen;
    QBrush m_BlackBrush;
};
