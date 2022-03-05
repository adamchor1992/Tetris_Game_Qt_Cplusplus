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
    static void drawBlock(BlockBase* block, QColor color);
    static void drawGameArena();
    static void drawSquare(const Coordinates& coordinates, QColor color, PlacedSquares& placedSquares);
    static void dropRow(int removedRow, PlacedSquares& placedSquares);
    static void eraseAllPlacedSquares(PlacedSquares& placedSquares);
    static void eraseBlock(BlockBase* block);
    static void eraseSquare(const Coordinates& coordinates, PlacedSquares& placedSquares);

private:
    [[maybe_unused]] static void debugDrawAllPossibleSquares();
    inline static QGraphicsScene* scene_ = nullptr;
};
