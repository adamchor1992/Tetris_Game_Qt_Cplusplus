#include "block_movement_manager.h"

bool BlockMovementManager::isHorizontalMovePossible(AbstractBlock* abstractBlock, Direction direction, const PlacedSquares& placedSquares)
{
    for(const auto& blockCoordinate : abstractBlock->getSquaresCoordinates())
    {
        int currentX = blockCoordinate.x;
        int currentY = blockCoordinate.y;

        if(direction == Direction::left)
        {
            int leftBlockX = currentX - 1;
            int leftBlockY = currentY;

            /*Check if there is left wall next to the block*/
            if(leftBlockX < GameParameters::Arena::minBlockColumns)
            {
                return false;
            }

            Coordinates leftOfBlockCoordinates{leftBlockX, leftBlockY};

            /*Check if there is any block to the left of current block*/
            if(placedSquares.getCoordinatesToSquaresMapping().contains(leftOfBlockCoordinates))
            {
                return false;
            }
        }
        else if(direction == Direction::right)
        {
            int rightBlockX = currentX + 1;
            int rightBlockY = currentY;

            /*Check if there is right wall next to the block*/
            if(rightBlockX > GameParameters::Arena::maxBlockColumns)
            {
                return false;
            }

            Coordinates rightOfBlockCoordinates{rightBlockX, rightBlockY};

            /*Check if there is any block to the right of current block*/
            if(placedSquares.getCoordinatesToSquaresMapping().contains(rightOfBlockCoordinates))
            {
                return false;
            }
        }
    }

    return true;
}


bool BlockMovementManager::isRotationPossible(const Coordinates& centralSquareCoordinates, const RotationCoefficients& rotationCoefficients, const PlacedSquares& placedSquares)
{
    Coordinates newSquare1 = centralSquareCoordinates + rotationCoefficients.getCoefficientsPair(0);
    Coordinates newSquare2 = centralSquareCoordinates + rotationCoefficients.getCoefficientsPair(1);
    Coordinates newSquare3 = centralSquareCoordinates + rotationCoefficients.getCoefficientsPair(2);

    if(!Coordinates::validateCoordinates(centralSquareCoordinates) || !Coordinates::validateCoordinates(newSquare1) || !Coordinates::validateCoordinates(newSquare2) ||
       !Coordinates::validateCoordinates(newSquare3))
    {
        return false;
    }

    const QVector<Coordinates> newCoordinates{centralSquareCoordinates, newSquare1, newSquare2, newSquare3};

    if(checkForOverlappingSquares(newCoordinates, placedSquares))
    {
        return false;
    }

    return true;
}

bool BlockMovementManager::checkForOverlappingSquares(const QVector<Coordinates>& blockCoordinates, const PlacedSquares& placedSquares)
{
    return std::ranges::any_of(blockCoordinates, [&placedSquares](const Coordinates& coordinates)
    {
        return placedSquares.getCoordinatesToSquaresMapping().contains(coordinates);
    });
}
