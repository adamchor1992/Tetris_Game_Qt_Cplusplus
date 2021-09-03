#pragma once

#include "placed_squares.h"
#include "common.h"
#include "coordinates.h"

class BlockBase
{
    friend std::ostream& operator<<(std::ostream& ofs, BlockBase& block);

public:
    explicit BlockBase(const QVector<int>& transformationCoefficientsVsCentralSquare_);
    virtual ~BlockBase();

    virtual void rotateBlock(const PlacedSquares&) = 0;

    static std::unique_ptr<BlockBase> makeBlock();

    QVector<QGraphicsRectItem*>& getGraphicsRectItems() {return squaresGraphicsRectItems_;}
    const QVector<Coordinates>& getBlockCoordinates() const {return blockCoordinates_;}

    bool isSquareOrBottomWallUnderBlock(const PlacedSquares& placedSquares) const;

    bool checkForOverlappingSquares(const QVector<Coordinates>& blockCoordinates, const PlacedSquares& placedSquares) const;
    bool checkMovePossibility(Direction direction, const PlacedSquares& placedSquares) const;
    void dropAndPlaceBlock(const PlacedSquares& placedSquares);
    void dropBlockOneLevel();
    void moveBlock(Direction direction);
    void placeBlock(PlacedSquares& placedSquares);
    bool processRotation(const PlacedSquares& placedSquares, const QVector<int>& rotationCoefficients);

protected:
    const Coordinates startingCentralSquareCoordinates_;

    QVector<QGraphicsRectItem*> squaresGraphicsRectItems_;
    QVector<Coordinates> blockCoordinates_;
    int currentRotation_;

private:
    bool checkRotationPossibility(const Coordinates& centralSquareCoordinates, const QVector<int>& rotationCoefficients, const PlacedSquares& placedSquares) const;

    const QVector<QColor> colors_ = {Qt::red, Qt::blue, Qt::green, Qt::yellow, Qt::cyan, Qt::magenta};
    QColor color_;
};
