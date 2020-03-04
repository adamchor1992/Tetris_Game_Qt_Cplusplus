#pragma once

#include <vector>
#include "placed_blocks.h"
#include "utilities.h"

class BlockBase
{
public:
    explicit BlockBase();
    virtual ~BlockBase();

    QVector<QPair<int, int> > GetBlockCoordinates();
    QColor GetColor();
    void DropBlockOneLevel();
    void DropAndPlaceBlock(PlacedBlocks const& placedBlocks);
    void MoveBlock(Direction direction);
    bool IsSquareOrBottomWallUnderBlock(PlacedBlocks const& placedBlocks);
    bool IsSquareOrLeftWallLeftOfBlock(PlacedBlocks const& placedBlocks);
    bool IsSquareOrRightWallRightOfBlock(PlacedBlocks const& placedBlocks);
    void SetBlockSquaresGraphicsRectItemPointers(QVector<QGraphicsRectItem*> blockSquaresGraphicsRectItemPointers)
    {
        m_BlockSquaresGraphicsRectItemPointers = blockSquaresGraphicsRectItemPointers;
    }
    QVector<QGraphicsRectItem*> const& GetBlockSquaresGraphicsRectItemPointers() const {return m_BlockSquaresGraphicsRectItemPointers;}

    virtual void RotateBlock() = 0;

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

private:
    /*Vector holding pointers to QGraphicsRectItem objects which block consists of*/
    QVector<QGraphicsRectItem*> m_BlockSquaresGraphicsRectItemPointers;
    bool m_BlockIsPresentOnScreen;
    QVector<QColor> m_Colors = {Qt::red, Qt::blue, Qt::white, Qt::green, Qt::yellow, Qt::cyan, Qt::magenta};
    QColor m_BlockColor;
};
