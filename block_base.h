#pragma once

#include <vector>
#include "placed_blocks.h"
#include "utilities.h"
#include "coordinates.h"

class BlockBase
{
public:
    explicit BlockBase();
    virtual ~BlockBase();

    const QVector<Coordinates>& GetBlockCoordinates() const {return m_BlockCoordinates;}
    QColor GetColor() const;
    void DropBlockOneLevel();
    void DropAndPlaceBlock(const PlacedBlocks& placedBlocks);
    void MoveBlock(Direction direction);
    bool ProcessRotation(const PlacedBlocks& placedBlocks, const QVector<int>& rotationCoefficients);
    bool IsSquareOrBottomWallUnderBlock(const PlacedBlocks& placedBlocks) const;
    bool IsSquareOrLeftWallLeftOfBlock(const PlacedBlocks& placedBlocks) const;
    bool IsSquareOrRightWallRightOfBlock(const PlacedBlocks& placedBlocks) const;
    void SetBlockSquaresGraphicsRectItemPointers(const QVector<QGraphicsRectItem*>& blockSquaresGraphicsRectItemPointers)
    {
        m_BlockSquaresGraphicsRectItemPointers = blockSquaresGraphicsRectItemPointers;
    }
    const QVector<QGraphicsRectItem*>& GetBlockSquaresGraphicsRectItemPointers() const {return m_BlockSquaresGraphicsRectItemPointers;}

    virtual void RotateBlock(const PlacedBlocks&) = 0;

protected:
    const Coordinates STARTING_CENTRAL_SQUARE_COORDINATES;
    QVector<Coordinates> m_BlockCoordinates;

    /*Vector holding pointers to QGraphicsRectItem objects which block consists of*/
    QVector<QGraphicsRectItem*> m_BlockSquaresGraphicsRectItemPointers;

private:
    const QVector<QColor> COLORS = {Qt::red, Qt::blue, Qt::green, Qt::yellow, Qt::cyan, Qt::magenta};
    QColor m_BlockColor;
};
