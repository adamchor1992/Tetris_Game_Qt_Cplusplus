#pragma once

#include "placed_squares.h"
#include "common.h"
#include "coordinates.h"
#include "random_generator.h"
#include "next_rotation_state_generator.h"

typedef int RotationState;

class BlockBase
{
    friend std::ostream& operator<<(std::ostream& ofs, BlockBase& block);

public:
    explicit BlockBase(const std::array<TransformationCoefficients, 3>& transformationCoefficientsVsCentralSquare_, int rotationCount);
    virtual ~BlockBase() = 0;

    virtual void rotate(const PlacedSquares& placedSquares) = 0;

    static std::unique_ptr<BlockBase> makeBlock(BlockShape shape = BlockShape::RANDOM);

    QVector<QGraphicsRectItem*>& getGraphicsRectItems() {return squaresGraphicsRectItems_;}
    [[nodiscard]] const QVector<Coordinates>& getBlockCoordinates() const {return blockCoordinates_;}

    [[nodiscard]] bool isSquareOrBottomWallUnderBlock(const PlacedSquares& placedSquares) const;

    [[nodiscard]] bool checkForOverlappingSquares(const QVector<Coordinates>& blockCoordinates, const PlacedSquares& placedSquares) const;
    [[nodiscard]] bool checkMovePossibility(Direction direction, const PlacedSquares& placedSquares) const;
    void dropAndPlaceBlock(const PlacedSquares& placedSquares);
    void dropBlockOneLevel();
    void processMove(Direction direction, const PlacedSquares& placedSquares);
    void placeBlock(PlacedSquares& placedSquares);
    void processRotation(const PlacedSquares& placedSquares, const std::array<RotationCoefficients, 3>& rotationCoefficients);
    [[nodiscard]] const QColor& getColor() const {return color_;}

protected:
    const Coordinates startingCentralSquareCoordinates_{5, 1};

    QVector<QGraphicsRectItem*> squaresGraphicsRectItems_;
    QVector<Coordinates> blockCoordinates_;
    int currentRotation_;
    NextRotationStateGenerator nextRotationStateGenerator_;

private:
    [[nodiscard]] bool checkRotationPossibility(const Coordinates& centralSquareCoordinates, const std::array<RotationCoefficients, 3>& rotationCoefficients, const PlacedSquares& placedSquares) const;

    const QColor color_;

    inline static RandomGenerator<QColor> randomColorGenerator{GameParameters::blockColors};
    inline static RandomGenerator<BlockShape> randomShapeGenerator{GameParameters::blockShapes};
};
