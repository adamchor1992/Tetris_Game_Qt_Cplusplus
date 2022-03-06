#include "block_base.h"
#include "drawer.h"
#include "random_number_generator.h"
#include "blocks/i_block.h"
#include "blocks/s_block.h"
#include "blocks/z_block.h"
#include "blocks/j_block.h"
#include "blocks/l_block.h"
#include "blocks/o_block.h"
#include "blocks/t_block.h"
#include "log_manager.h"

BlockBase::BlockBase(const QVector<int>& transformationCoefficientsVsCentralSquare_) : startingCentralSquareCoordinates_(5, 1)
{
    static RandomNumberGenerator randomNumberGenerator(0, colors_.size() - 1);
    color_ = colors_.at(randomNumberGenerator.generateRandomNumber());

    const Coordinates square1Coordinates(startingCentralSquareCoordinates_.getX() + transformationCoefficientsVsCentralSquare_.at(0),
                                         startingCentralSquareCoordinates_.getY() + transformationCoefficientsVsCentralSquare_.at(1));
    const Coordinates square2Coordinates(startingCentralSquareCoordinates_.getX() + transformationCoefficientsVsCentralSquare_.at(2),
                                         startingCentralSquareCoordinates_.getY() + transformationCoefficientsVsCentralSquare_.at(3));
    const Coordinates square3Coordinates(startingCentralSquareCoordinates_.getX() + transformationCoefficientsVsCentralSquare_.at(4),
                                         startingCentralSquareCoordinates_.getY() + transformationCoefficientsVsCentralSquare_.at(5));

    blockCoordinates_.append(startingCentralSquareCoordinates_);
    blockCoordinates_.append(square1Coordinates);
    blockCoordinates_.append(square2Coordinates);
    blockCoordinates_.append(square3Coordinates);

    currentRotation_ = 0;
}

BlockBase::~BlockBase()
{
    Drawer::eraseBlock(this);
}

std::unique_ptr<BlockBase> BlockBase::makeBlock(QString shape)
{
    std::unique_ptr<BlockBase> block;

    static std::map<unsigned int, QString> numberToShapeMapping = { {0, "S"}, {1, "Z"}, {2, "I"}, {3, "J"}, {4, "L"}, {5, "O"}, {6, "T"} };
    static RandomNumberGenerator randomNumberGenerator(0, numberToShapeMapping.size() - 1);

    if(shape.isEmpty())
    {
        shape = numberToShapeMapping.at(randomNumberGenerator.generateRandomNumber());
    }

    if(shape == "S")
    {
        block = std::make_unique<SBlock>();
    }
    else if(shape == "Z")
    {
        block = std::make_unique<ZBlock>();
    }
    else if(shape == "I")
    {
        block = std::make_unique<IBlock>();
    }
    else if(shape == "J")
    {
        block = std::make_unique<JBlock>();
    }
    else if(shape == "L")
    {
        block = std::make_unique<LBlock>();
    }
    else if(shape == "O")
    {
        block = std::make_unique<OBlock>();
    }
    else if(shape == "T")
    {
        block = std::make_unique<TBlock>();
    }
    else
    {
        throw std::runtime_error("Undefined block shape");
    }

    logFile << "MakeBlock at: " << (*block) << "\t\t\t";

    Drawer::drawBlock(block.get(), block->color_);

    return block;
}

void BlockBase::moveBlock(Direction direction)
{
    if(direction == Direction::left)
    {
        for(int i = 0; i < blockCoordinates_.size(); i++)
        {
            int currentX = blockCoordinates_.at(i).getX();
            int currentY = blockCoordinates_.at(i).getY();

            int newX = currentX - 1;
            int newY = currentY;

            blockCoordinates_[i].modify(newX, newY);

            squaresGraphicsRectItems_.at(i)->moveBy(-GameArenaParameters::blockSquareSize, 0);
        }
    }
    else if(direction == Direction::right)
    {
        for(int i = 0; i < blockCoordinates_.size(); i++)
        {
            int currentX = blockCoordinates_.at(i).getX();
            int currentY = blockCoordinates_.at(i).getY();

            int newX = currentX + 1;
            int newY = currentY;

            blockCoordinates_[i].modify(newX, newY);

            squaresGraphicsRectItems_.at(i)->moveBy(+GameArenaParameters::blockSquareSize, 0);
        }
    }
}

bool BlockBase::checkMovePossibility(Direction direction, const PlacedSquares& placedSquares) const
{
    for(const auto& blockCoordinate : blockCoordinates_)
    {
        int currentX = blockCoordinate.getX();
        int currentY = blockCoordinate.getY();

        if(direction == Direction::left)
        {
            int leftBlockX = currentX - 1;
            int leftBlockY = currentY;

            /*Check if there is left wall next to the block*/
            if(leftBlockX < GameArenaParameters::minBlockColumns)
            {
                return false;
            }

            Coordinates leftOfBlockCoordinates(leftBlockX, leftBlockY);

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

            Coordinates rightOfBlockCoordinates(rightBlockX, rightBlockY);

            /*Check if there is any block to the left of current block*/
            if(placedSquares.getCoordinatesToSquaresMapping().value(rightOfBlockCoordinates) != nullptr)
            {
                return false;
            }
        }
    }

    return true;
}

bool BlockBase::checkRotationPossibility(const Coordinates& centralSquareCoordinates, const QVector<int>& rotationCoefficients, const PlacedSquares& placedSquares) const
{
    int newCentralSquareX = centralSquareCoordinates.getX();
    int newCentralSquareY = centralSquareCoordinates.getY();

    int newSquare1X = centralSquareCoordinates.getX() + rotationCoefficients.at(0);
    int newSquare1Y = centralSquareCoordinates.getY() + rotationCoefficients.at(1);

    int newSquare2X = centralSquareCoordinates.getX() + rotationCoefficients.at(2);
    int newSquare2Y = centralSquareCoordinates.getY() + rotationCoefficients.at(3);

    int newSquare3X = centralSquareCoordinates.getX() + rotationCoefficients.at(4);
    int newSquare3Y = centralSquareCoordinates.getY() + rotationCoefficients.at(5);

    if(!Coordinates::validateCoordinates(newCentralSquareX, newCentralSquareY) ||
            !Coordinates::validateCoordinates(newSquare1X, newSquare1Y)||
            !Coordinates::validateCoordinates(newSquare2X, newSquare2Y)||
            !Coordinates::validateCoordinates(newSquare3X, newSquare3Y))
    {
        return false;
    }

    const QVector<Coordinates> newCoordinates {Coordinates(newCentralSquareX, newCentralSquareY), Coordinates(newSquare1X, newSquare1Y), Coordinates(newSquare2X, newSquare2Y), Coordinates(newSquare3X, newSquare3Y)};

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

    for(const auto& blockCoordinate : blockCoordinates_)
    {
        placedSquares.addSquare(blockCoordinate, PlacedSquares::placedSquares_color, placedSquares);
    }
}

bool BlockBase::processRotation(const PlacedSquares& placedSquares, const QVector<int>& rotationCoefficients)
{
    const Coordinates centralSquare_coordinates(blockCoordinates_.at(0).getX(), blockCoordinates_.at(0).getY());

    if(checkRotationPossibility(centralSquare_coordinates, rotationCoefficients, placedSquares))
    {
        const int newCentralSquareX = centralSquare_coordinates.getX();
        const int newCentralSquareY = centralSquare_coordinates.getY();
        const int newSquare1X = centralSquare_coordinates.getX() + rotationCoefficients.at(0);
        const int newSquare1Y = centralSquare_coordinates.getY() + rotationCoefficients.at(1);
        const int newSquare2X = centralSquare_coordinates.getX() + rotationCoefficients.at(2);
        const int newSquare2Y = centralSquare_coordinates.getY() + rotationCoefficients.at(3);
        const int newSquare3X = centralSquare_coordinates.getX() + rotationCoefficients.at(4);
        const int newSquare3Y = centralSquare_coordinates.getY() + rotationCoefficients.at(5);

        const QPair<int, int> centralSquareCoordinatesDifference {newCentralSquareX - blockCoordinates_[0].getX(), newCentralSquareY - blockCoordinates_[0].getY()};
        const QPair<int, int> square1CoordinatesDifference {newSquare1X - blockCoordinates_[1].getX(), newSquare1Y - blockCoordinates_[1].getY()};
        const QPair<int, int> square2CoordinatesDifference {newSquare2X - blockCoordinates_[2].getX(), newSquare2Y - blockCoordinates_[2].getY()};
        const QPair<int, int> square3CoordinatesDifference {newSquare3X - blockCoordinates_[3].getX(), newSquare3Y - blockCoordinates_[3].getY()};

        squaresGraphicsRectItems_.at(0)->moveBy(centralSquareCoordinatesDifference.first * GameArenaParameters::blockSquareSize,
                                                     centralSquareCoordinatesDifference.second * GameArenaParameters::blockSquareSize);

        squaresGraphicsRectItems_.at(1)->moveBy(square1CoordinatesDifference.first * GameArenaParameters::blockSquareSize,
                                                     square1CoordinatesDifference.second * GameArenaParameters::blockSquareSize);

        squaresGraphicsRectItems_.at(2)->moveBy(square2CoordinatesDifference.first * GameArenaParameters::blockSquareSize,
                                                     square2CoordinatesDifference.second * GameArenaParameters::blockSquareSize);

        squaresGraphicsRectItems_.at(3)->moveBy(square3CoordinatesDifference.first * GameArenaParameters::blockSquareSize,
                                                     square3CoordinatesDifference.second * GameArenaParameters::blockSquareSize);

        blockCoordinates_[0].modify(newCentralSquareX, newCentralSquareY);
        blockCoordinates_[1].modify(newSquare1X, newSquare1Y);
        blockCoordinates_[2].modify(newSquare2X, newSquare2Y);
        blockCoordinates_[3].modify(newSquare3X, newSquare3Y);

        return true;
    }
    else
    {
        return false;
    }
}

bool BlockBase::isSquareOrBottomWallUnderBlock(const PlacedSquares& placedSquares) const
{
    for(const auto& blockCoordinate : blockCoordinates_)
    {
        int currentX = blockCoordinate.getX();
        int currentY = blockCoordinate.getY();

        int belowBlockX = currentX;
        int belowBlockY = currentY + 1;

        /*Check if there is bottom wall below the current block*/
        if(belowBlockY > GameArenaParameters::maxBlockRows)
        {
            return true;
        }

        Coordinates belowBlockCoordinates(belowBlockX, belowBlockY);

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
        int x = blockCoordinates_[i].getX();
        int y = blockCoordinates_[i].getY();

        blockCoordinates_[i].modify(x, y + 1);

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
        os << "[" << coordinates.getX() << "," << coordinates.getY() << "]";
    }

    return os;
}
