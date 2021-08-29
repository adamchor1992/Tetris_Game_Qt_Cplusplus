#include "block_base.h"
#include "drawer.h"
#include "random_number_generator.h"

BlockBase::BlockBase() : STARTING_CENTRAL_SQUARE_COORDINATES(5, 1)
{
    static RandomNumberGenerator randomNumberGenerator(0, COLORS.size() - 1);
    m_BlockColor = COLORS.at(randomNumberGenerator.GenerateRandomNumber());
}

BlockBase::~BlockBase()
{
    for(auto& pointer : m_BlockSquaresGraphicsRectItemPointers)
    {
        pointer = nullptr;
    }
}

void BlockBase::MoveBlock(Direction direction)
{
    if(direction == Direction::left)
    {
        for(int i = 0; i < m_BlockCoordinates.size(); i++)
        {
            int currentX = m_BlockCoordinates.at(i).GetX();
            int currentY = m_BlockCoordinates.at(i).GetY();

            /*Coordinate X decreases*/
            int newX = currentX - 1;
            /*Coordinate Y does not change*/
            int newY = currentY;

            m_BlockCoordinates[i].Modify(newX, newY);

            m_BlockSquaresGraphicsRectItemPointers.at(i)->moveBy(-GameArenaParameters::BLOCK_SQUARE_SIZE, 0);
        }
    }
    else if(direction == Direction::right)
    {
        for(int i = 0; i < m_BlockCoordinates.size(); i++)
        {
            int currentX = m_BlockCoordinates.at(i).GetX();
            int currentY = m_BlockCoordinates.at(i).GetY();

            /*Coordinate X increases*/
            int newX = currentX + 1;
            /*Coordinate Y does not change*/
            int newY = currentY;

            m_BlockCoordinates[i].Modify(newX, newY);

            m_BlockSquaresGraphicsRectItemPointers.at(i)->moveBy(+GameArenaParameters::BLOCK_SQUARE_SIZE, 0);
        }
    }
}

bool BlockBase::IsSquareOrLeftWallLeftOfBlock(const PlacedBlocks& placedBlocks) const
{
    for(int i = 0; i < m_BlockCoordinates.size(); i++)
    {
        int currentX = m_BlockCoordinates.at(i).GetX();
        int currentY = m_BlockCoordinates.at(i).GetY();

        /*Coordinate X decreases*/
        int leftBlockX = currentX - 1;
        /*Coordinate Y does not change*/
        int leftBlockY = currentY;

        /*Check if there is left wall next to the block*/
        if(leftBlockX < 1)
        {
            return true;
        }

        Coordinates leftOfBlockCoordinates(leftBlockX,leftBlockY);

        /*Check if there is any block to the left of current block*/
        if(placedBlocks.GetPlacedBlocksMap().value(leftOfBlockCoordinates) == PlacedBlocks::SquarePresence::SQUARE_PRESENT)
        {
            return true;
        }
    }

    return false;
}

bool BlockBase::IsSquareOrRightWallRightOfBlock(const PlacedBlocks& placedBlocks) const
{
    for(int i = 0; i<m_BlockCoordinates.size(); i++)
    {
        int currentX = m_BlockCoordinates.at(i).GetX();
        int currentY = m_BlockCoordinates.at(i).GetY();

        /*Coordinate X increases*/
        int rightBlockX = currentX + 1;
        /*Coordinate Y does not change*/
        int rightBlockY = currentY;

        /*Check if there is wall next to the block*/
        if(rightBlockX > GameArenaParameters::MAX_BLOCK_COLUMNS)
        {
            return true;
        }

        Coordinates rightOfBlockCoordinates(rightBlockX,rightBlockY);

        /*Check if there is any block to the right of the current block*/
        if(placedBlocks.GetPlacedBlocksMap().value(rightOfBlockCoordinates) == PlacedBlocks::SquarePresence::SQUARE_PRESENT)
        {
            return true;
        }
    }

    return false;
}

bool BlockBase::ProcessRotation(const PlacedBlocks& placedBlocks, const QVector<int>& rotationCoefficients)
{
    const Coordinates centralSquareCordinates(m_BlockCoordinates.at(0).GetX(), m_BlockCoordinates.at(0).GetY());

    if(Coordinates::CheckIfRotationIsPossible(centralSquareCordinates, rotationCoefficients, placedBlocks))
    {
        const int newCentralSquareX = centralSquareCordinates.GetX();
        const int newCentralSquareY = centralSquareCordinates.GetY();
        const int newSquare1X = centralSquareCordinates.GetX() + rotationCoefficients.at(0);
        const int newSquare1Y = centralSquareCordinates.GetY() + rotationCoefficients.at(1);
        const int newSquare2X = centralSquareCordinates.GetX() + rotationCoefficients.at(2);
        const int newSquare2Y = centralSquareCordinates.GetY() + rotationCoefficients.at(3);
        const int newSquare3X = centralSquareCordinates.GetX() + rotationCoefficients.at(4);
        const int newSquare3Y = centralSquareCordinates.GetY() + rotationCoefficients.at(5);

        const QPair<int, int> centralSquareDifference {newCentralSquareX - m_BlockCoordinates[0].GetX(), newCentralSquareY - m_BlockCoordinates[0].GetY()};
        const QPair<int, int> square1Difference {newSquare1X - m_BlockCoordinates[1].GetX(), newSquare1Y - m_BlockCoordinates[1].GetY()};
        const QPair<int, int> square2Difference {newSquare2X - m_BlockCoordinates[2].GetX(), newSquare2Y - m_BlockCoordinates[2].GetY()};
        const QPair<int, int> square3Difference {newSquare3X - m_BlockCoordinates[3].GetX(), newSquare3Y - m_BlockCoordinates[3].GetY()};

        m_BlockSquaresGraphicsRectItemPointers.at(0)->moveBy(centralSquareDifference.first * GameArenaParameters::BLOCK_SQUARE_SIZE,
                                                             centralSquareDifference.second * GameArenaParameters::BLOCK_SQUARE_SIZE);

        m_BlockSquaresGraphicsRectItemPointers.at(1)->moveBy(square1Difference.first * GameArenaParameters::BLOCK_SQUARE_SIZE,
                                                             square1Difference.second * GameArenaParameters::BLOCK_SQUARE_SIZE);

        m_BlockSquaresGraphicsRectItemPointers.at(2)->moveBy(square2Difference.first * GameArenaParameters::BLOCK_SQUARE_SIZE,
                                                             square2Difference.second * GameArenaParameters::BLOCK_SQUARE_SIZE);

        m_BlockSquaresGraphicsRectItemPointers.at(3)->moveBy(square3Difference.first * GameArenaParameters::BLOCK_SQUARE_SIZE,
                                                             square3Difference.second * GameArenaParameters::BLOCK_SQUARE_SIZE);

        m_BlockCoordinates[0].Modify(newCentralSquareX, newCentralSquareY);
        m_BlockCoordinates[1].Modify(newSquare1X, newSquare1Y);
        m_BlockCoordinates[2].Modify(newSquare2X, newSquare2Y);
        m_BlockCoordinates[3].Modify(newSquare3X, newSquare3Y);

        return true;
    }
    else
    {
        qDebug() << "ROTATION REJECTED";
        return false;
    }
}

bool BlockBase::IsSquareOrBottomWallUnderBlock(const PlacedBlocks& placedBlocks) const
{
    for(int i = 0; i < m_BlockCoordinates.size(); i++)
    {
        int currentX = m_BlockCoordinates.at(i).GetX();
        int currentY = m_BlockCoordinates.at(i).GetY();

        /*Coordinate X does not change*/
        int belowBlockX = currentX;
        /*Coordinate Y increases*/
        int belowBlockY = currentY + 1;

        /*Check if there is bottom wall below the current block*/
        if(belowBlockY > GameArenaParameters::MAX_BLOCK_ROWS)
        {
            return true;
        }

        Coordinates belowBlockCoordinates(belowBlockX,belowBlockY);

        /*Check if there is any block below the current block*/
        if(placedBlocks.GetPlacedBlocksMap().value(belowBlockCoordinates) == PlacedBlocks::SquarePresence::SQUARE_PRESENT)
        {
            return true;
        }
    }
    return false;
}

QColor BlockBase::GetColor() const
{
    return m_BlockColor;
}

void BlockBase::DropBlockOneLevel()
{
    for(int i = 0; i < m_BlockCoordinates.size(); i++)
    {
        int x = m_BlockCoordinates[i].GetX();
        int y = m_BlockCoordinates[i].GetY();

        m_BlockCoordinates[i].Modify(x, y + 1);

        m_BlockSquaresGraphicsRectItemPointers.at(i)->moveBy(0, GameArenaParameters::BLOCK_SQUARE_SIZE);
    }
}

void BlockBase::DropAndPlaceBlock(const PlacedBlocks& placedBlocks)
{
    while(!IsSquareOrBottomWallUnderBlock(placedBlocks))
    {
        DropBlockOneLevel();
    }
}
