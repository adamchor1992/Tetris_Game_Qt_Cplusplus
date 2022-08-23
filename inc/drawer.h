#pragma once

#include "placed_squares.h"
#include "coordinates.h"
#include "block_base.h"

#include <QGraphicsScene>

class Drawer
{
public:
    Drawer() = delete;

    static void setScene(QGraphicsScene* scene) {scene_ = scene;}
    static void drawGameArena();
    static Square* drawBlockSquare(const Coordinates& coordinates, const QColor& color);
    static void drawBlock(BlockBase* block, std::array<Coordinates, BlockBase::blockSize>& blockCoordinates);
    static void eraseBlock(BlockBase* block);
    static void eraseSquare(Square* square, PlacedSquares& placedSquares);

private:
    [[maybe_unused]] static void debugDrawAllPossibleSquares();
    inline static QGraphicsScene* scene_ = nullptr;
};
