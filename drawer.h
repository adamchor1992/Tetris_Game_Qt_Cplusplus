#pragma once

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
    Drawer() = delete;
    Drawer(const Drawer&) = delete;
    Drawer& operator=(Drawer&) = delete;
    Drawer(const Drawer&&) = delete;
    Drawer& operator=(Drawer&&) = delete;

    static void SetScene(QGraphicsScene* pScene) {m_pScene = pScene;}
    static void DrawGameArena();
    static QVector<QGraphicsRectItem*> DrawBlock(const QVector<QPair<int, int> >& blockCoordinates, QColor randomColor);
    static void DrawAllPlacedBlocks(const PlacedBlocks& placedBlocks);
    static void EraseBlock(const QVector<QGraphicsRectItem *>& blockRectGraphicPointers);

private:
    static QGraphicsScene* m_pScene;

    static void DrawSquare(int x, int y, QBrush brush);
    static void DrawAllPossibleSquares();
    static void RemoveAllPlacedBlocks();
};
