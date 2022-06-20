#pragma once

#include "placed_squares.h"
#include "coordinates.h"
#include "block_base.h"

#include <QGraphicsScene>

class Drawer
{
public:
    Drawer() = delete;
    Drawer(const Drawer&) = delete;
    Drawer& operator=(Drawer&) = delete;
    Drawer(const Drawer&&) = delete;
    Drawer& operator=(Drawer&&) = delete;

    static void setScene(QGraphicsScene* scene) {scene_ = scene;}
    static void drawGameArena();
    static void dropRow(int removedRow, PlacedSquares& placedSquares);
    static void eraseAllPlacedSquares(PlacedSquares& placedSquares);
    static void eraseBlock(BlockBase* block);
    static void eraseSquare(const Coordinates& coordinates, PlacedSquares& placedSquares);
    static void drawBlock(BlockBase* block);
    static QGraphicsRectItem* drawBlockSquare(const Coordinates& coordinates, QColor color);

private:
    [[maybe_unused]] static void debugDrawAllPossibleSquares();
    inline static QGraphicsScene* scene_ = nullptr;
};
