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

void Drawer::drawSquare(const Coordinates& coordinates, QColor color, PlacedSquares& placedSquares)
{
    placedSquares.getCoordinatesToSquaresMapping()[coordinates] = scene_->addRect((coordinates.getX() - 1) * GameArenaParameters::blockSquareSize + GameArenaParameters::wallOffset,
                                                                                  (coordinates.getY() - 1) * GameArenaParameters::blockSquareSize + GameArenaParameters::wallOffset,
                                                                                  GameArenaParameters::blockSquareSize,
                                                                                  GameArenaParameters::blockSquareSize,
                                                                                  Qt::NoPen,
                                                                                  color);
}

void Drawer::eraseSquare(const Coordinates& coordinates, PlacedSquares& placedSquares)
{
    scene_->removeItem(placedSquares.getCoordinatesToSquaresMapping().value(coordinates));
    placedSquares.getCoordinatesToSquaresMapping()[coordinates] = nullptr;
}

void Drawer::drawBlock(BlockBase* block, QColor color)
{
    QPen pen(color);
    QBrush brush(color);

    for(int i = 0 ; i < block->getBlockCoordinates().size(); i++)
    {
        block->getGraphicsRectItems().append(scene_->addRect((block->getBlockCoordinates().at(i).getX() - 1) * GameArenaParameters::blockSquareSize + GameArenaParameters::wallOffset,
                                                             (block->getBlockCoordinates().at(i).getY() - 1) * GameArenaParameters::blockSquareSize + GameArenaParameters::wallOffset,
                                                             GameArenaParameters::blockSquareSize,
                                                             GameArenaParameters::blockSquareSize,
                                                             pen,
                                                             brush));
    }
}

void Drawer::eraseBlock(BlockBase* block)
{
    for(auto& graphicsRectItem : block->getGraphicsRectItems())
    {
        scene_->removeItem(graphicsRectItem);
    }

    block->getGraphicsRectItems().clear();
}

void Drawer::dropRow(int removedRow, PlacedSquares& placedSquares)
{
    for(auto& coordinates : placedSquares.getCoordinatesToSquaresMapping().keys())
    {
        if(coordinates.getY() < removedRow)
        {
            if(placedSquares.getCoordinatesToSquaresMapping().value(coordinates) != nullptr)
            {
                placedSquares.getCoordinatesToSquaresMapping().value(coordinates)->moveBy(0, GameArenaParameters::blockSquareSize);
            }
        }
    }
}

void Drawer::eraseAllPlacedSquares(PlacedSquares& placedSquares)
{
    for(auto& coordinates : placedSquares.getCoordinatesToSquaresMapping().keys())
    {
        if(placedSquares.getCoordinatesToSquaresMapping().value(coordinates) != nullptr)
        {
            Drawer::eraseSquare(coordinates, placedSquares);
        }
    }
}

[[maybe_unused]] void Drawer::debugDrawAllPossibleSquares()
{
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);

    for(int column = 0; column < GameArenaParameters::maxBlockColumns; ++column)
    {
        for(int row = 0; row < GameArenaParameters::maxBlockRows; ++row)
        {
            /*Different block color every second column*/
            if(column % 2 == 0)
            {
                if(row % 2 == 0) /*Different block color every second row*/
                {
                    scene_->addRect(column * GameArenaParameters::blockSquareSize + GameArenaParameters::wallOffset,
                                    row * GameArenaParameters::blockSquareSize + GameArenaParameters::wallOffset,
                                    GameArenaParameters::blockSquareSize,
                                    GameArenaParameters::blockSquareSize,
                                    Qt::NoPen,
                                    blueBrush);
                }
                else
                {
                    scene_->addRect(column * GameArenaParameters::blockSquareSize + GameArenaParameters::wallOffset,
                                    row * GameArenaParameters::blockSquareSize + GameArenaParameters::wallOffset,
                                    GameArenaParameters::blockSquareSize,
                                    GameArenaParameters::blockSquareSize,
                                    Qt::NoPen,
                                    redBrush);
                }
            }
            else
            {
                if(row % 2 != 0)
                {
                    scene_->addRect(column * GameArenaParameters::blockSquareSize + GameArenaParameters::wallOffset,
                                    row * GameArenaParameters::blockSquareSize + GameArenaParameters::wallOffset,
                                    GameArenaParameters::blockSquareSize,
                                    GameArenaParameters::blockSquareSize,
                                    Qt::NoPen,
                                    blueBrush);
                }
                else
                {
                    scene_->addRect(column * GameArenaParameters::blockSquareSize + GameArenaParameters::wallOffset,
                                    row * GameArenaParameters::blockSquareSize + GameArenaParameters::wallOffset,
                                    GameArenaParameters::blockSquareSize,
                                    GameArenaParameters::blockSquareSize,
                                    Qt::NoPen,
                                    redBrush);
                }
            }
        }
    }
}
