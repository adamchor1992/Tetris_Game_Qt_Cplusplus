#pragma once

#include <vector>
#include "placed_squares.h"
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
    void DropAndPlaceBlock(const PlacedSquares& placedBlocks);
    void MoveBlock(Direction direction);
    bool ProcessRotation(const PlacedSquares& placedBlocks, const QVector<int>& rotationCoefficients);
    bool IsSquareOrBottomWallUnderBlock(const PlacedSquares& placedBlocks) const;
    bool CheckMovePossibility(Direction direction, const PlacedSquares& placedBlocks) const;
    bool CheckIfRotationIsPossible(const Coordinates& centralSquareCoordinates, const QVector<int>& rotationCoefficients, const PlacedSquares& placedBlocks) const;
    bool CheckForOverlappingSquares(const QVector<Coordinates>& blockCoordinates, const PlacedSquares& placedBlocks) const;
    void SetBlockSquaresGraphicsRectItemPointers(const QVector<QGraphicsRectItem*>& blockSquaresGraphicsRectItemPointers) {m_BlockSquaresGraphicsRectItemPointers = blockSquaresGraphicsRectItemPointers;}
    const QVector<QGraphicsRectItem*>& GetBlockSquaresGraphicsRectItemPointers() const {return m_BlockSquaresGraphicsRectItemPointers;}

    virtual void RotateBlock(const PlacedSquares&) = 0;

    static std::unique_ptr<BlockBase> MakeBlock();

protected:
    const Coordinates STARTING_CENTRAL_SQUARE_COORDINATES;
    QVector<Coordinates> m_BlockCoordinates;

    /*Vector holding pointers to QGraphicsRectItem objects which block consists of*/
    QVector<QGraphicsRectItem*> m_BlockSquaresGraphicsRectItemPointers;

private:
    const QVector<QColor> COLORS = {Qt::red, Qt::blue, Qt::green, Qt::yellow, Qt::cyan, Qt::magenta};
    QColor m_BlockColor;
};
