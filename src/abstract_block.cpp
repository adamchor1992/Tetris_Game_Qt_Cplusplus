#include "abstract_block.h"
#include "view/window.h"
#include "log_manager.h"
#include "block_movement_manager.h"

AbstractBlock::AbstractBlock(const QColor& color, const TransformationCoefficients& transformationCoefficientsVsCentralSquare, int rotationCount) :
        COLOR(color), nextRotationStateGenerator_(rotationCount)
{
    std::array<Coordinates, AbstractBlock::SIZE> blockSquaresCoordinates{STARTING_CENTRAL_SQUARE_COORDINATES,
                                                                         STARTING_CENTRAL_SQUARE_COORDINATES + transformationCoefficientsVsCentralSquare.getCoefficientsPair(0),
                                                                         STARTING_CENTRAL_SQUARE_COORDINATES + transformationCoefficientsVsCentralSquare.getCoefficientsPair(1),
                                                                         STARTING_CENTRAL_SQUARE_COORDINATES + transformationCoefficientsVsCentralSquare.getCoefficientsPair(2)};

    for(auto& blockCoordinate : blockSquaresCoordinates)
    {
        squares_.emplace_back(std::make_shared<Square>(blockCoordinate, COLOR));
    }
}

AbstractBlock::~AbstractBlock()
{
    emit blockUpdatedEvent(this);
}

[[nodiscard]] QVector<Coordinates> AbstractBlock::getSquaresCoordinates() const
{
    return {getSquareCoordinates(0), getSquareCoordinates(1), getSquareCoordinates(2), getSquareCoordinates(3)};
}

[[nodiscard]] const Coordinates& AbstractBlock::getSquareCoordinates(int i) const
{
    return squares_.at(i)->getCoordinates();
}

void AbstractBlock::processMove(Direction direction, const PlacedSquares& placedSquares)
{
    if(direction == Direction::left)
    {
        if(BlockMovementManager::isHorizontalMovePossible(this, direction, placedSquares))
        {
            for(int i = 0; i < SIZE; i++)
            {
                squares_.at(i)->move(-1, 0);
            }

            emit blockUpdatedEvent(this);
        }
    }
    else if(direction == Direction::right)
    {
        if(BlockMovementManager::isHorizontalMovePossible(this, direction, placedSquares))
        {
            for(int i = 0; i < SIZE; i++)
            {
                squares_.at(i)->move(+1, 0);
            }
        }

        emit blockUpdatedEvent(this);
    }
}

void AbstractBlock::processRotation(const PlacedSquares& placedSquares, const RotationCoefficients& rotationCoefficients)
{
    const Coordinates centralSquare_coordinates{getSquareCoordinates(0)};

    if(BlockMovementManager::isRotationPossible(centralSquare_coordinates, rotationCoefficients, placedSquares))
    {
        const Coordinates newSquare1{centralSquare_coordinates + rotationCoefficients.getCoefficientsPair(0)};
        const Coordinates newSquare2{centralSquare_coordinates + rotationCoefficients.getCoefficientsPair(1)};
        const Coordinates newSquare3{centralSquare_coordinates + rotationCoefficients.getCoefficientsPair(2)};

        Coordinates centralSquareCoordinatesDifference = centralSquare_coordinates - getSquareCoordinates(0);
        Coordinates square1CoordinatesDifference{newSquare1 - getSquareCoordinates(1)};
        Coordinates square2CoordinatesDifference{newSquare2 - getSquareCoordinates(2)};
        Coordinates square3CoordinatesDifference{newSquare3 - getSquareCoordinates(3)};

        squares_.at(0)->move(centralSquareCoordinatesDifference.x, centralSquareCoordinatesDifference.y);
        squares_.at(1)->move(square1CoordinatesDifference.x, square1CoordinatesDifference.y);
        squares_.at(2)->move(square2CoordinatesDifference.x, square2CoordinatesDifference.y);
        squares_.at(3)->move(square3CoordinatesDifference.x, square3CoordinatesDifference.y);

        currentRotation_ = nextRotationStateGenerator_();

        emit blockUpdatedEvent(this);
    }
}

bool AbstractBlock::isSquareOrBottomWallUnderBlock(const PlacedSquares& placedSquares) const
{
    for(const auto& blockCoordinates : getSquaresCoordinates())
    {
        auto [currentX, currentY] = blockCoordinates;

        int belowBlockX = currentX;
        int belowBlockY = currentY + 1;

        /*Check if there is bottom wall below the current block*/
        if(belowBlockY > GameParameters::Arena::maxBlockRows)
        {
            return true;
        }

        Coordinates belowBlockCoordinates{belowBlockX, belowBlockY};

        /*Check if there is any block below the current block*/
        if(placedSquares.getCoordinatesToSquaresMapping().contains(belowBlockCoordinates))
        {
            return true;
        }
    }

    return false;
}

void AbstractBlock::place(PlacedSquares& placedSquares)
{
    placedSquares.placeBlock(this);
    emit blockUpdatedEvent(this);
}

void AbstractBlock::dropBlockOneLevel()
{
    for(int i = 0; i < SIZE; i++)
    {
        squares_.at(i)->move(0, +1);
    }

    emit blockUpdatedEvent(this);
}

void AbstractBlock::dropAndPlace(const PlacedSquares& placedSquares)
{
    while(!isSquareOrBottomWallUnderBlock(placedSquares))
    {
        dropBlockOneLevel();
    }
}

std::ostream& operator<<(std::ostream& os, AbstractBlock& block)
{
    for(const auto& coordinates : block.getSquaresCoordinates())
    {
        os << coordinates;
    }

    return os;
}
