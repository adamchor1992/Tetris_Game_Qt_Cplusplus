#pragma once

#include "placed_squares.h"
#include "common.h"
#include "coordinates.h"
#include "random_generator.h"

class BlockBase
{
    friend std::ostream& operator<<(std::ostream& ofs, BlockBase& block);

public:
    explicit BlockBase(const QVector<int>& transformationCoefficientsVsCentralSquare_);
    virtual ~BlockBase();

    virtual void rotateBlock(const PlacedSquares&) = 0;

    static std::unique_ptr<BlockBase> makeBlock(BlockShape shape = BlockShape::RANDOM);

    QVector<QGraphicsRectItem*>& getGraphicsRectItems() {return squaresGraphicsRectItems_;}
    [[nodiscard]] const QVector<Coordinates>& getBlockCoordinates() const {return blockCoordinates_;}

    [[nodiscard]] bool isSquareOrBottomWallUnderBlock(const PlacedSquares& placedSquares) const;

    [[nodiscard]] bool checkForOverlappingSquares(const QVector<Coordinates>& blockCoordinates, const PlacedSquares& placedSquares) const;
    [[nodiscard]] bool checkMovePossibility(Direction direction, const PlacedSquares& placedSquares) const;
    void dropAndPlaceBlock(const PlacedSquares& placedSquares);
    void dropBlockOneLevel();
    void moveBlock(Direction direction);
    void placeBlock(PlacedSquares& placedSquares);
    bool processRotation(const PlacedSquares& placedSquares, const QVector<int>& rotationCoefficients);
    [[nodiscard]] QColor getColor() const {return color_;}

protected:
    const Coordinates startingCentralSquareCoordinates_{5, 1};

    QVector<QGraphicsRectItem*> squaresGraphicsRectItems_;
    QVector<Coordinates> blockCoordinates_;
    int currentRotation_;

private:
    [[nodiscard]] bool checkRotationPossibility(const Coordinates& centralSquareCoordinates, const QVector<int>& rotationCoefficients, const PlacedSquares& placedSquares) const;

    const QColor color_;

    inline static const QVector<QColor> colors_ = {Qt::red, Qt::blue, Qt::green, Qt::yellow, Qt::cyan, Qt::magenta};
    inline static RandomGenerator<QColor> randomColorGenerator{colors_};

    inline static const QVector<BlockShape> shapes_ = {BlockShape::S, BlockShape::Z, BlockShape::I, BlockShape::J, BlockShape::L, BlockShape::O, BlockShape::T};
    inline static RandomGenerator<BlockShape> randomShapeGenerator{shapes_};
};
