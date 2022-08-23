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
    explicit BlockBase(const QColor& color, const TransformationCoefficients& transformationCoefficientsVsCentralSquare, int rotationCount);
    virtual ~BlockBase() = 0;

    virtual void rotate(const PlacedSquares& placedSquares) = 0;

    QVector<Square*>& getSquares() {return squares_;}
    [[nodiscard]] QVector<Coordinates> extractAllSquareCoordinates() const;
    [[nodiscard]] Coordinates& getSquareCoordinates(int i) const;
    [[nodiscard]] bool isSquareOrBottomWallUnderBlock(const PlacedSquares& placedSquares) const;
    [[nodiscard]] bool checkForOverlappingSquares(const QVector<Coordinates>& blockCoordinates, const PlacedSquares& placedSquares) const;
    [[nodiscard]] bool checkMovePossibility(Direction direction, const PlacedSquares& placedSquares) const;
    void dropAndPlaceBlock(const PlacedSquares& placedSquares);
    void dropBlockOneLevel();
    void processMove(Direction direction, const PlacedSquares& placedSquares);
    void placeBlock(PlacedSquares& placedSquares);
    void processRotation(const PlacedSquares& placedSquares, const RotationCoefficients& rotationCoefficients);
    [[nodiscard]] const QColor& getColor() const {return color_;}

    static const int blockSize = 4;

protected:
    int currentRotation_ = 0;

private:
    const QColor color_;
    static constexpr Coordinates startingCentralSquareCoordinates_{5, 1};
    QVector<Square*> squares_;
    NextRotationStateGenerator nextRotationStateGenerator_;

    [[nodiscard]] bool checkRotationPossibility(const Coordinates& centralSquareCoordinates, const RotationCoefficients& rotationCoefficients, const PlacedSquares& placedSquares) const;
};
