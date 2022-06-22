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
    static Square* drawBlockSquare(const Coordinates& coordinates, QColor color);
    static void drawBlock(BlockBase* block, std::array<Coordinates, 4>& blockCoordinates);
    static void eraseBlock(BlockBase* block);
    static void eraseSquare(const Coordinates& coordinates, PlacedSquares& placedSquares);
    static void eraseSquare(Square* square);

private:
    [[maybe_unused]] static void debugDrawAllPossibleSquares();
    inline static QGraphicsScene* scene_ = nullptr;
};
