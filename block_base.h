#pragma once

#include <vector>
#include "placed_blocks.h"
#include "utilities.h"

class BlockBase
{
public:
    explicit BlockBase(QString shape = "I");
    virtual ~BlockBase();

    void MoveBlock(Direction direction);
    QVector<int> GetBlockCoordinates();
    bool IsSquaresLeftOfBlock(PlacedBlocks const* p_PlacedBlocks);
    bool IsSquaresRightOfBlock(PlacedBlocks const* p_PlacedBlocks);
    bool IsSquaresUnderBlock(PlacedBlocks const* p_PlacedBlocks);
    QColor GetColor();
    void DropBlockCoordinates();

    virtual void RotateBlock() = 0;

protected:
    QString m_Shape;

    int m_CentralSquareX = 0;
    int m_CentralSquareY = 0;
    int m_Square1PositionX = 0;
    int m_Square1PositionY = 0;
    int m_Square2PositionX = 0;
    int m_Square2PositionY = 0;
    int m_Square3PositionX = 0;
    int m_Square3PositionY = 0;

    QVector<int> m_BlockCoordinates;
    QVector<QGraphicsRectItem*> m_BlockGraphicsItemsPtrs;

private:
    QVector<QGraphicsRectItem*> m_GraphicalPointersVector;
    bool m_BlockIsPresentOnScreen;
    QVector<QColor> m_Colors = {Qt::red, Qt::blue, Qt::white, Qt::green, Qt::yellow, Qt::cyan, Qt::magenta};
    QColor m_BlockColor;
};
