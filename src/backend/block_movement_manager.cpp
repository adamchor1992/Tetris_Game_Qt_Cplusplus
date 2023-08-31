#include "block_movement_manager.h"

BlockMovementSimulationResult BlockMovementManager::simulateHorizontalMove(const Block& block, Direction direction, const PlacedSquares& placedSquares)
{
    std::pair<int, int> offset;

    if(direction == Direction::LEFT)
    {
        offset = std::pair<int, int>{-1, 0};
    }
    else if(direction == Direction::RIGHT)
    {
        offset = std::pair<int, int>{+1, 0};
    }

    Coordinates newCentralSquareCoordinates = block.getSquareCoordinates(0) + offset;
    Coordinates newSquare1Coordinates = block.getSquareCoordinates(1) + offset;
    Coordinates newSquare2Coordinates = block.getSquareCoordinates(2) + offset;
    Coordinates newSquare3Coordinates = block.getSquareCoordinates(3) + offset;

    if(!Coordinates::validateCoordinates(newCentralSquareCoordinates) || !Coordinates::validateCoordinates(newSquare1Coordinates) || !Coordinates::validateCoordinates(newSquare2Coordinates) || !Coordinates::validateCoordinates(newSquare3Coordinates))
    {
        return {};
    }

    const BlockCoordinatesArray newBlockCoordinates{newCentralSquareCoordinates, newSquare1Coordinates, newSquare2Coordinates, newSquare3Coordinates};

    if(checkForOverlappingSquares(newBlockCoordinates, placedSquares))
    {
        return {};
    }

    return BlockMovementSimulationResult{newBlockCoordinates};
}

BlockRotationSimulationResult BlockMovementManager::simulateRotation(const Block& block, const PlacedSquares& placedSquares)
{
    const RotationStateToRotationCoefficientsContainerMapping& rotationStateToRotationCoefficientsContainerMapping = block.getRotationCoefficients();
    const Coordinates centralSquareCoordinates = block.getCentralSquareCoordinates();

    Coordinates newSquare1Coordinates = centralSquareCoordinates + rotationStateToRotationCoefficientsContainerMapping.at(block.getRotationStateIterator().peekNext()).getRotationCoefficientsPair(0);
    Coordinates newSquare2Coordinates = centralSquareCoordinates + rotationStateToRotationCoefficientsContainerMapping.at(block.getRotationStateIterator().peekNext()).getRotationCoefficientsPair(1);
    Coordinates newSquare3Coordinates = centralSquareCoordinates + rotationStateToRotationCoefficientsContainerMapping.at(block.getRotationStateIterator().peekNext()).getRotationCoefficientsPair(2);

    if(!Coordinates::validateCoordinates(centralSquareCoordinates) || !Coordinates::validateCoordinates(newSquare1Coordinates) || !Coordinates::validateCoordinates(newSquare2Coordinates) || !Coordinates::validateCoordinates(newSquare3Coordinates))
    {
        return {};
    }

    const BlockCoordinatesArray newBlockCoordinates{centralSquareCoordinates, newSquare1Coordinates, newSquare2Coordinates, newSquare3Coordinates};

    if(checkForOverlappingSquares(newBlockCoordinates, placedSquares))
    {
        return {};
    }

    return BlockRotationSimulationResult{newBlockCoordinates};
}

bool BlockMovementManager::checkForOverlappingSquares(const Block& block, const PlacedSquares& placedSquares)
{
    return checkForOverlappingSquares(block.getAllSquaresCoordinates(), placedSquares);
}

bool BlockMovementManager::checkForOverlappingSquares(const BlockCoordinatesArray& blockCoordinates, const PlacedSquares& placedSquares)
{
    return std::ranges::any_of(blockCoordinates, [&placedSquares](const Coordinates& coordinates)
    {
        return placedSquares.isFieldOccupied(coordinates);
    });
}

void BlockMovementManager::processMove(Block& block, const BlockMovementSimulationResult& movementSimulationResult)
{
    block.setBlockCoordinates(movementSimulationResult.getBlockCoordinates());
}

void BlockMovementManager::processRotation(Block& block, const BlockRotationSimulationResult& rotationSimulationResult)
{
    block.setBlockCoordinates(rotationSimulationResult.getBlockCoordinates());
    block.getRotationStateIterator().advance();
}

bool BlockMovementManager::isSquareOrBottomWallUnderBlock(const Block& block, const PlacedSquares& placedSquares)
{
    return std::ranges::any_of(block.getAllSquaresCoordinates(), [&placedSquares](const Coordinates& coordinates)
    {
        auto[currentX, currentY] = coordinates;

        int belowBlockX = currentX;
        int belowBlockY = currentY + 1;

        if(belowBlockY == Config::Arena::BOTTOM_EDGE_Y)
        {
            return true;
        }

        Coordinates belowBlockCoordinates{belowBlockX, belowBlockY};

        if(placedSquares.isFieldOccupied(belowBlockCoordinates))
        {
            return true;
        }

        return false;
    });
}

void BlockMovementManager::lowerBlockOneRow(Block& block)
{
    for(Coordinates& squareCoordinates : block.getAllSquaresCoordinates())
    {
        squareCoordinates += {0, 1};
    }
}

void BlockMovementManager::dropBlock(Block& block, PlacedSquares& placedSquares)
{
    while(!BlockMovementManager::isSquareOrBottomWallUnderBlock(block, placedSquares))
    {
        lowerBlockOneRow(block);
    }
}

void BlockMovementManager::placeBlock(Block& block, PlacedSquares& placedSquares)
{
    placedSquares.placeBlock(block);
}
