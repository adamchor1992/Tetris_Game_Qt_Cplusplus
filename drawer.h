#pragma once

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QPen>
#include <QBrush>
#include <QVector>
#include <QColor>
#include <placed_squares.h>

#include "coordinates.h"

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
    static QVector<QGraphicsRectItem*> DrawBlock(const QVector<Coordinates>& blockCoordinates, QColor randomColor);
    static void DrawAllPlacedBlocks(const PlacedSquares &placedBlocks);
    static void RemoveAllPlacedBlocks();
    static void Debug_PrintItemsCurrentlyOnScene();

private:
    static QGraphicsScene* m_pScene;

    static void DrawSquare(const Coordinates& coordinates, QBrush brush);
    static void Debug_DrawAllPossibleSquares();
};
