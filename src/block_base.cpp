#include "block_base.h"
#include "drawer.h"
#include "blocks/i_block.h"
#include "blocks/s_block.h"
#include "blocks/z_block.h"
#include "blocks/j_block.h"
#include "blocks/l_block.h"
#include "blocks/o_block.h"
#include "blocks/t_block.h"
#include "log_manager.h"

BlockBase::BlockBase(const QVector<TransformationCoefficients>& transformationCoefficientsVsCentralSquare_) : color_(randomColorGenerator())
{
    blockCoordinates_.append(startingCentralSquareCoordinates_);
    blockCoordinates_.append(startingCentralSquareCoordinates_ + transformationCoefficientsVsCentralSquare_.at(0));
    blockCoordinates_.append(startingCentralSquareCoordinates_ + transformationCoefficientsVsCentralSquare_.at(1));
    blockCoordinates_.append(startingCentralSquareCoordinates_ + transformationCoefficientsVsCentralSquare_.at(2));

    currentRotation_ = 0;
}

BlockBase::~BlockBase()
{
    Drawer::eraseBlock(this);
}

std::unique_ptr<BlockBase> BlockBase::makeBlock(BlockShape shape)
{
    std::unique_ptr<BlockBase> block;

    if(shape == BlockShape::RANDOM)
    {
        shape = randomShapeGenerator();
    }

    switch (shape)
    {
        case BlockShape::S:
            block = std::make_unique<SBlock>();
            break;
        case BlockShape::Z:
            block = std::make_unique<ZBlock>();
            break;
        case BlockShape::I:
            block = std::make_unique<IBlock>();
            break;
        case BlockShape::J:
            block = std::make_unique<JBlock>();
            break;
        case BlockShape::L:
            block = std::make_unique<LBlock>();
            break;
        case BlockShape::O:
            block = std::make_unique<OBlock>();
            break;
        case BlockShape::T:
            block = std::make_unique<TBlock>();
            break;
        case BlockShape::RANDOM:
            throw std::runtime_error("Random shape block error");
    }

    logFile << "MakeBlock at: " << (*block) << "\t\t\t";

    Drawer::drawBlock(block.get());

    return block;
}

void BlockBase::moveBlock(Direction direction)
{
    if(direction == Direction::left)
    {
        for(int i = 0; i < blockCoordinates_.size(); i++)
        {
            blockCoordinates_[i] += {-1, 0};
            squaresGraphicsRectItems_.at(i)->moveBy(-GameArenaParameters::blockSquareSize, 0);
        }
    }
    else if(direction == Direction::right)
    {
        for(int i = 0; i < blockCoordinates_.size(); i++)
        {
            blockCoordinates_[i] += {+1, 0};
            squaresGraphicsRectItems_.at(i)->moveBy(+GameArenaParameters::blockSquareSize, 0);
        }
    }
}

bool BlockBase::checkMovePossibility(Direction direction, const PlacedSquares& placedSquares) const
{
    for(const auto& blockCoordinate : blockCoordinates_)
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
            if(placedSquares.getCoordinatesToSquaresMapping().value(leftOfBlockCoordinates) != nullptr)
            {
                return false;
            }
        }
        else if(direction == Direction::right)
        {
            int rightBlockX = currentX + 1;
            int rightBlockY = currentY;

            /*Check if there is wall next to the block*/
            if(rightBlockX > GameArenaParameters::maxBlockColumns)
            {
                return false;
            }

            Coordinates rightOfBlockCoordinates{rightBlockX, rightBlockY};

            /*Check if there is any block to the left of current block*/
            if(placedSquares.getCoordinatesToSquaresMapping().value(rightOfBlockCoordinates) != nullptr)
            {
                return false;
            }
        }
    }

    return true;
}

bool BlockBase::checkRotationPossibility(const Coordinates& centralSquareCoordinates, const QVector<RotationCoefficients>& rotationCoefficients, const PlacedSquares& placedSquares) const
{
    Coordinates newSquare1 = centralSquareCoordinates + rotationCoefficients.at(0);
    Coordinates newSquare2 = centralSquareCoordinates + rotationCoefficients.at(1);
    Coordinates newSquare3 = centralSquareCoordinates + rotationCoefficients.at(2);

    if(!Coordinates::validateCoordinates(centralSquareCoordinates) ||
       !Coordinates::validateCoordinates(newSquare1)||
       !Coordinates::validateCoordinates(newSquare2)||
       !Coordinates::validateCoordinates(newSquare3))
    {
        return false;
    }

    const QVector<Coordinates> newCoordinates {centralSquareCoordinates, newSquare1, newSquare2, newSquare3};

    if(checkForOverlappingSquares(newCoordinates, placedSquares))
    {
        return false;
    }

    return true;
}

bool BlockBase::checkForOverlappingSquares(const QVector<Coordinates>& blockCoordinates, const PlacedSquares& placedSquares) const
{
    for(auto& coordinates : blockCoordinates)
    {
        if(placedSquares.getCoordinatesToSquaresMapping().value(coordinates) != nullptr)
        {
            return true;
        }
    }

    return false;
}

void BlockBase::placeBlock(PlacedSquares& placedSquares)
{
    logFile << "PlaceBlock at: " << (*this) << std::endl;
    placedSquares.stealSquaresFromBlock(blockCoordinates_, squaresGraphicsRectItems_, getColor(), placedSquares);
}

bool BlockBase::processRotation(const PlacedSquares& placedSquares, const QVector<RotationCoefficients>& rotationCoefficients)
{
    const Coordinates centralSquare_coordinates{blockCoordinates_.at(0).x, blockCoordinates_.at(0).y};

    if(checkRotationPossibility(centralSquare_coordinates, rotationCoefficients, placedSquares))
    {
        const Coordinates newSquare1 {centralSquare_coordinates + rotationCoefficients.at(0)};
        const Coordinates newSquare2 {centralSquare_coordinates + rotationCoefficients.at(1)};
        const Coordinates newSquare3 {centralSquare_coordinates + rotationCoefficients.at(2)};

        Coordinates centralSquareCoordinatesDifference = centralSquare_coordinates - blockCoordinates_[0];
        Coordinates square1CoordinatesDifference {newSquare1 - blockCoordinates_[1]};
        Coordinates square2CoordinatesDifference {newSquare2 - blockCoordinates_[2]};
        Coordinates square3CoordinatesDifference {newSquare3 - blockCoordinates_[3]};

        squaresGraphicsRectItems_.at(0)->moveBy(centralSquareCoordinatesDifference.x * GameArenaParameters::blockSquareSize,
                                                     centralSquareCoordinatesDifference.y * GameArenaParameters::blockSquareSize);

        squaresGraphicsRectItems_.at(1)->moveBy(square1CoordinatesDifference.x * GameArenaParameters::blockSquareSize,
                                                     square1CoordinatesDifference.y * GameArenaParameters::blockSquareSize);

        squaresGraphicsRectItems_.at(2)->moveBy(square2CoordinatesDifference.x * GameArenaParameters::blockSquareSize,
                                                     square2CoordinatesDifference.y * GameArenaParameters::blockSquareSize);

        squaresGraphicsRectItems_.at(3)->moveBy(square3CoordinatesDifference.x * GameArenaParameters::blockSquareSize,
                                                     square3CoordinatesDifference.y * GameArenaParameters::blockSquareSize);

        blockCoordinates_[0] = centralSquare_coordinates;
        blockCoordinates_[1] = newSquare1;
        blockCoordinates_[2] = newSquare2;
        blockCoordinates_[3] = newSquare3;

        return true;
    }
    else
    {
        return false;
    }
}

bool BlockBase::isSquareOrBottomWallUnderBlock(const PlacedSquares& placedSquares) const
{
    for(const auto& blockCoordinates : blockCoordinates_)
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
        if(placedSquares.getCoordinatesToSquaresMapping().value(belowBlockCoordinates) != nullptr)
        {
            return true;
        }
    }

    return false;
}

void BlockBase::dropBlockOneLevel()
{
    for(int i = 0; i < blockCoordinates_.size(); i++)
    {
        blockCoordinates_[i] += {0, +1};
        squaresGraphicsRectItems_.at(i)->moveBy(0, GameArenaParameters::blockSquareSize);
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
    for(auto& coordinates : block.getBlockCoordinates())
    {
        os << "[" << coordinates.x << "," << coordinates.y << "]";
    }

    return os;
}
