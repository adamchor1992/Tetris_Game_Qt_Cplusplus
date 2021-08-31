#pragma once

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
    void DropAndPlaceBlock(const PlacedSquares& placedSquares);
    void MoveBlock(Direction direction);
    bool ProcessRotation(const PlacedSquares& placedSquares, const QVector<int>& rotationCoefficients);
    bool IsSquareOrBottomWallUnderBlock(const PlacedSquares& placedSquares) const;
    bool CheckMovePossibility(Direction direction, const PlacedSquares& placedSquares) const;
    bool CheckIfRotationIsPossible(const Coordinates& centralSquareCoordinates, const QVector<int>& rotationCoefficients, const PlacedSquares& placedSquares) const;
    bool CheckForOverlappingSquares(const QVector<Coordinates>& blockCoordinates, const PlacedSquares& placedSquares) const;
    QVector<QGraphicsRectItem*>& GetBlockSquaresGraphicsRectItemPointers() {return m_BlockSquaresGraphicsRectItemPointers;}
    void PlaceBlock(PlacedSquares& placedSquares);

    virtual void RotateBlock(const PlacedSquares&) = 0;

    static std::unique_ptr<BlockBase> MakeBlock();

    void DropSquareOneLevel();
protected:
    const Coordinates STARTING_CENTRAL_SQUARE_COORDINATES;
    QVector<Coordinates> m_BlockCoordinates;

    /*Vector holding pointers to QGraphicsRectItem objects which block consists of*/
    /*It can be static because there is only one block allowed at a time*/
    static QVector<QGraphicsRectItem*> m_BlockSquaresGraphicsRectItemPointers;

private:
    const QVector<QColor> COLORS = {Qt::red, Qt::blue, Qt::green, Qt::yellow, Qt::cyan, Qt::magenta};
    QColor m_BlockColor;
};
