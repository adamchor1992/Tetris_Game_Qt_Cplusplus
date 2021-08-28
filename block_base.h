#pragma once

#include <vector>
#include "placed_blocks.h"
#include "utilities.h"

class BlockBase
{
public:
    explicit BlockBase();
    virtual ~BlockBase();

    QVector<QPair<int, int> > GetBlockCoordinates() const;
    QColor GetColor() const;
    void DropBlockOneLevel();
    void DropAndPlaceBlock(const PlacedBlocks& placedBlocks);
    void MoveBlock(Direction direction);
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
    int m_CentralSquareX;
    int m_CentralSquareY;
    int m_Square1PositionX;
    int m_Square1PositionY;
    int m_Square2PositionX;
    int m_Square2PositionY;
    int m_Square3PositionX;
    int m_Square3PositionY;

    QVector<QPair<int, int> > m_BlockCoordinates;

    /*Vector holding pointers to QGraphicsRectItem objects which block consists of*/
    QVector<QGraphicsRectItem*> m_BlockSquaresGraphicsRectItemPointers;

private:
    QVector<QColor> m_Colors = {Qt::red, Qt::blue, Qt::green, Qt::yellow, Qt::cyan, Qt::magenta};
    QColor m_BlockColor;
};
