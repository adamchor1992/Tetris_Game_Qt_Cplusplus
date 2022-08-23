#include "drawer.h"
#include "common.h"
#include "coordinates.h"

void Drawer::drawGameArena()
{
    QBrush whiteBrush(GameArenaParameters::wallColor);
    QPen wallPen(whiteBrush, GameArenaParameters::wallThickness);

    /*Left wall*/
    scene_->addLine(GameArenaParameters::leftBorderX + GameArenaParameters::leftBorderOffsetX,
                    GameArenaParameters::bottomY,
                    GameArenaParameters::leftBorderX + GameArenaParameters::leftBorderOffsetX,
                    GameArenaParameters::topY,
                    wallPen);

    /*Right wall*/
    scene_->addLine(GameArenaParameters::rightBorderX + GameArenaParameters::rightBorderOffsetX,
                    GameArenaParameters::bottomY,
                    GameArenaParameters::rightBorderX + GameArenaParameters::rightBorderOffsetX,
                    GameArenaParameters::topY,
                    wallPen);

    /*Bottom wall*/
    scene_->addLine(GameArenaParameters::leftBorderX,
                    GameArenaParameters::bottomY + GameArenaParameters::bottomOffsetY,
                    GameArenaParameters::rightBorderX,
                    GameArenaParameters::bottomY + GameArenaParameters::bottomOffsetY,
                    wallPen);

    /*Top wall*/
    scene_->addLine(GameArenaParameters::leftBorderX,
                    GameArenaParameters::topY + GameArenaParameters::topOffsetY,
                    GameArenaParameters::rightBorderX,
                    GameArenaParameters::topY + GameArenaParameters::topOffsetY,
                    wallPen);
}

Square* Drawer::drawBlockSquare(const Coordinates& coordinates, const QColor& color)
{
    auto* square = new Square(coordinates, color);
    scene_->addItem(square);
    return square;
}

void Drawer::drawBlock(BlockBase* block, std::array<Coordinates, BlockBase::blockSize>& blockCoordinates)
{
    for(const auto& blockCoordinate : blockCoordinates)
    {
        block->getSquares().append(drawBlockSquare(blockCoordinate, block->getColor()));
    }
}

void Drawer::eraseSquare(Square* square, PlacedSquares& placedSquares)
{
    scene_->removeItem(square);
    placedSquares.getCoordinatesToSquaresMapping().remove(square->getCoordinates());
    delete square;
}

void Drawer::eraseBlock(BlockBase* block)
{
    for(auto& graphicsRectItem: block->getSquares())
    {
        if(graphicsRectItem)
        {
            scene_->removeItem(graphicsRectItem);
        }
    }
}

[[maybe_unused]] void Drawer::debugDrawAllPossibleSquares()
{
    QColor red(Qt::red);
    QColor blue(Qt::blue);

    for(int column = 1; column <= GameArenaParameters::maxBlockColumns; ++column)
    {
        for(int row = 1; row <= GameArenaParameters::maxBlockRows; ++row)
        {
            /*Different block color every second column*/
            if(column % 2 == 0)
            {
                /*Different block color every second row*/
                if(row % 2 == 0)
                {
                    drawBlockSquare(Coordinates{column, row}, blue);
                }
                else
                {
                    drawBlockSquare(Coordinates{column, row}, red);
                }
            }
            else
            {
                if(row % 2 != 0)
                {
                    drawBlockSquare(Coordinates{column, row}, blue);
                }
                else
                {
                    drawBlockSquare(Coordinates{column, row}, red);
                }
            }
        }
    }
}
