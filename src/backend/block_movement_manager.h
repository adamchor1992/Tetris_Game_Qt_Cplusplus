#pragma once

#include "simulation_result.h"

class BlockMovementSimulationResult;

class BlockMovementManager
{
public:
    [[nodiscard]] static BlockMovementSimulationResult simulateHorizontalMove(const Block& block, Direction direction, const PlacedSquares& placedSquares);
    [[nodiscard]] static BlockRotationSimulationResult simulateRotation(const Block& block, const PlacedSquares& placedSquares);

    static void processMove(Block& block, const BlockMovementSimulationResult& movementSimulationResult);
    static void processRotation(Block& block, const BlockRotationSimulationResult& rotationSimulationResult);

    static bool isSquareOrBottomWallUnderBlock(const Block& block, const PlacedSquares& placedSquares);

    [[nodiscard]] static bool checkForOverlappingSquares(const Block& block, const PlacedSquares& placedSquares);
    [[nodiscard]] static bool checkForOverlappingSquares(const BlockCoordinatesArray& blockCoordinates, const PlacedSquares& placedSquares);

    static void lowerBlockOneRow(Block& block);
    static void dropBlock(Block& block, PlacedSquares& placedSquares);
    static void placeBlock(Block& block, PlacedSquares& placedSquares);
};
