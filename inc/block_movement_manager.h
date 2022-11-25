#pragma once

#include "common.h"
#include "placed_squares.h"
#include "abstract_block.h"

class BlockMovementManager
{
public:
    [[nodiscard]] static bool isHorizontalMovePossible(AbstractBlock* abstractBlock, Direction direction, const PlacedSquares& placedSquares);
    [[nodiscard]] static bool isRotationPossible(const Coordinates& centralSquareCoordinates, const RotationCoefficients& rotationCoefficients, const PlacedSquares& placedSquares);
    [[nodiscard]] static bool checkForOverlappingSquares(const QVector<Coordinates>& blockCoordinates, const PlacedSquares& placedSquares);
};
