#include "block_base.h"
#include "drawer.h"
#include "log_manager.h"

BlockBase::BlockBase(const QColor& color, const TransformationCoefficients& transformationCoefficientsVsCentralSquare, int rotationCount) :
        color_(color), nextRotationStateGenerator_(rotationCount)
{
    std::array<Coordinates, BlockBase::blockSize> blockCoordinates{startingCentralSquareCoordinates_,
                                                startingCentralSquareCoordinates_ + transformationCoefficientsVsCentralSquare.getCoefficientsPair(0),
                                                startingCentralSquareCoordinates_ + transformationCoefficientsVsCentralSquare.getCoefficientsPair(1),
                                                startingCentralSquareCoordinates_ + transformationCoefficientsVsCentralSquare.getCoefficientsPair(2)};

    Drawer::drawBlock(this, blockCoordinates);

    logFile << "Block created at " << *this << std::endl;
}

BlockBase::~BlockBase()
{
    Drawer::eraseBlock(this);
}

[[nodiscard]] QVector<Coordinates> BlockBase::extractAllSquareCoordinates() const
{
    return {getSquareCoordinates(0), getSquareCoordinates(1), getSquareCoordinates(2), getSquareCoordinates(3)};
}

[[nodiscard]] Coordinates& BlockBase::getSquareCoordinates(int i) const
{
    return squares_.at(i)->getCoordinates();
}

bool BlockBase::checkMovePossibility(Direction direction, const PlacedSquares& placedSquares) const
{
    for(const auto& blockCoordinate: extractAllSquareCoordinates())
    {
        int currentX = blockCoordinate.x;
        int currentY = blockCoordinate.y;

        if(direction == Direction::left)
        {
            int leftBlockX = currentX - 1;
            int leftBlockY = currentY;

            /*Check if there is left wall next to the block*/
            if(leftBlockX < GameArenaParameters::minBlockColumns)
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
            if(rightBlockX > GameArenaParameters::maxBlockColumns)
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

void BlockBase::processMove(Direction direction, const PlacedSquares& placedSquares)
{
    if(direction == Direction::left)
    {
        if(checkMovePossibility(Direction::left, placedSquares))
        {
            for(int i = 0; i < blockSize; i++)
            {
                squares_.at(i)->move(-1, 0);
            }
        }
    }
    else if(direction == Direction::right)
    {
        if(checkMovePossibility(Direction::right, placedSquares))
        {
            for(int i = 0; i < blockSize; i++)
            {
                squares_.at(i)->move(+1, 0);
            }
        }
    }
}

bool BlockBase::checkRotationPossibility(const Coordinates& centralSquareCoordinates,
                                         const RotationCoefficients& rotationCoefficients,
                                         const PlacedSquares& placedSquares) const
{
    Coordinates newSquare1 = centralSquareCoordinates + rotationCoefficients.getCoefficientsPair(0);
    Coordinates newSquare2 = centralSquareCoordinates + rotationCoefficients.getCoefficientsPair(1);
    Coordinates newSquare3 = centralSquareCoordinates + rotationCoefficients.getCoefficientsPair(2);

    if(!Coordinates::validateCoordinates(centralSquareCoordinates) || !Coordinates::validateCoordinates(newSquare1) ||
       !Coordinates::validateCoordinates(newSquare2) || !Coordinates::validateCoordinates(newSquare3))
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

void BlockBase::processRotation(const PlacedSquares& placedSquares, const RotationCoefficients& rotationCoefficients)
{
    const Coordinates centralSquare_coordinates{getSquareCoordinates(0)};

    if(checkRotationPossibility(centralSquare_coordinates, rotationCoefficients, placedSquares))
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
    }
}

bool BlockBase::checkForOverlappingSquares(const QVector<Coordinates>& blockCoordinates, const PlacedSquares& placedSquares) const
{
    return std::ranges::any_of(blockCoordinates, [&placedSquares](const Coordinates& coordinates)
    {
        return placedSquares.getCoordinatesToSquaresMapping().contains(coordinates);
    });
}

bool BlockBase::isSquareOrBottomWallUnderBlock(const PlacedSquares& placedSquares) const
{
    for(const auto& blockCoordinates: extractAllSquareCoordinates())
    {
        auto [currentX, currentY] = blockCoordinates;

        int belowBlockX = currentX;
        int belowBlockY = currentY + 1;

        /*Check if there is bottom wall below the current block*/
        if(belowBlockY > GameArenaParameters::maxBlockRows)
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

void BlockBase::placeBlock(PlacedSquares& placedSquares)
{
    logFile << "Place block at " << (*this) << std::endl;
    placedSquares.stealSquaresFromBlock(extractAllSquareCoordinates(), squares_, placedSquares);
}

void BlockBase::dropBlockOneLevel()
{
    for(int i = 0; i < blockSize; i++)
    {
        squares_.at(i)->move(0, +1);
    }
}

void BlockBase::dropAndPlaceBlock(const PlacedSquares& placedSquares)
{
    while(!isSquareOrBottomWallUnderBlock(placedSquares))
    {
        dropBlockOneLevel();
    }
}

std::ostream& operator<<(std::ostream& os, BlockBase& block)
{
    for(const auto& coordinates: block.extractAllSquareCoordinates())
    {
        os << "[" << coordinates.x << "," << coordinates.y << "]";
    }

    return os;
}
