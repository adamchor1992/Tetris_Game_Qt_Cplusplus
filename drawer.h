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
#include "block_base.h"

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
    static void EraseAllPlacedSquares(PlacedSquares& placedSquares);

    static void DrawSquare(const Coordinates& coordinates, QColor color, PlacedSquares& placedSquares);
    static void EraseSquare(const Coordinates& coordinates, PlacedSquares& placedSquares);
    static void DrawBlock(BlockBase* block, QColor color);
    static void EraseBlock(BlockBase* block);

    static void DropRow(int removedRow, PlacedSquares& placedSquares);

private:
    static QGraphicsScene* m_pScene;
    static void Debug_DrawAllPossibleSquares();
};
