#include "block_base.h"
#include "drawer.h"
#include "random_number_generator.h"

BlockBase::BlockBase()
{
    static RandomNumberGenerator randomNumberGenerator(0, m_Colors.size() - 1);
    m_BlockColor = m_Colors.at(randomNumberGenerator.GenerateRandomNumber());

    m_CentralSquareX = 5;
    m_CentralSquareY = 1;
    m_Square1PositionX = 0;
    m_Square1PositionY = 0;
    m_Square2PositionX = 0;
    m_Square2PositionY = 0;
    m_Square3PositionX = 0;
    m_Square3PositionY = 0;
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
        for(int i=0; i < m_BlockCoordinates.size(); i++)
        {
            int currentX = m_BlockCoordinates.at(i).first;
            int currentY = m_BlockCoordinates.at(i).second;

            /*Coordinate X decreases*/
            int newX = currentX - 1;
            /*Coordinate Y does not change*/
            int newY = currentY;

            m_BlockCoordinates[i].first = newX;
            m_BlockCoordinates[i].second = newY;
        }
    }
    else if(direction == Direction::right)
    {
        for(int i=0; i < m_BlockCoordinates.size(); i++)
        {
            int currentX = m_BlockCoordinates.at(i).first;
            int currentY = m_BlockCoordinates.at(i).second;

            /*Coordinate X increases*/
            int newX = currentX + 1;
            /*Coordinate Y does not change*/
            int newY = currentY;

            m_BlockCoordinates[i].first = newX;
            m_BlockCoordinates[i].second = newY;
        }
    }

    Drawer::EraseBlock(m_BlockSquaresGraphicsRectItemPointers);
    m_BlockSquaresGraphicsRectItemPointers = Drawer::DrawBlock(GetBlockCoordinates(), GetColor());
}

void BlockBase::RotateBlock(const PlacedBlocks&)
{
    qDebug() << "Base class RotateBlock() method called";
    assert(false);
}

bool BlockBase::IsSquareOrLeftWallLeftOfBlock(const PlacedBlocks& placedBlocks) const
{
    for(int i=0; i < m_BlockCoordinates.size(); i++)
    {
        int currentX = m_BlockCoordinates.at(i).first;
        int currentY = m_BlockCoordinates.at(i).second;

        /*Coordinate X decreases*/
        int leftBlockX = currentX - 1;
        /*Coordinate Y does not change*/
        int leftBlockY = currentY;

        /*Check if there is left wall next to the block*/
        if(leftBlockX < 1)
        {
            return true;
        }

        QPair<int,int> leftOfBlockCoordinatesPair(leftBlockX,leftBlockY);

        /*Check if there is any block to the left of current block*/
        if(placedBlocks.GetPlacedBlocksMap().value(leftOfBlockCoordinatesPair) == PlacedBlocks::SquarePresence::SQUARE_PRESENT)
        {
            return true;
        }
    }

    return false;
}

bool BlockBase::IsSquareOrRightWallRightOfBlock(const PlacedBlocks& placedBlocks) const
{
    for(int i=0; i<m_BlockCoordinates.size(); i++)
    {
        int currentX = m_BlockCoordinates.at(i).first;
        int currentY = m_BlockCoordinates.at(i).second;

        /*Coordinate X increases*/
        int rightBlockX = currentX + 1;
        /*Coordinate Y does not change*/
        int rightBlockY = currentY;

        /*Check if there is wall next to the block*/
        if(rightBlockX > GameArenaParameters::MAX_BLOCK_COLUMNS)
        {
            return true;
        }

        QPair<int,int> rightOfBlockCoordinatesPair(rightBlockX,rightBlockY);

        /*Check if there is any block to the right of the current block*/
        if(placedBlocks.GetPlacedBlocksMap().value(rightOfBlockCoordinatesPair) == PlacedBlocks::SquarePresence::SQUARE_PRESENT)
        {
            return true;
        }
    }

    return false;
}

bool BlockBase::IsSquareOrBottomWallUnderBlock(const PlacedBlocks& placedBlocks) const
{
    for(int i=0; i < m_BlockCoordinates.size(); i++)
    {
        int currentX = m_BlockCoordinates.at(i).first;
        int currentY = m_BlockCoordinates.at(i).second;

        /*Coordinate X does not change*/
        int belowBlockX = currentX;
        /*Coordinate Y increases*/
        int belowBlockY = currentY + 1;

        /*Check if there is bottom wall below the current block*/
        if(belowBlockY > GameArenaParameters::MAX_BLOCK_ROWS)
        {
            return true;
        }

        QPair<int, int> belowBlockCoordinatesPair(belowBlockX,belowBlockY);

        /*Check if there is any block below the current block*/
        if(placedBlocks.GetPlacedBlocksMap().value(belowBlockCoordinatesPair) == PlacedBlocks::SquarePresence::SQUARE_PRESENT)
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
    for(int i=0; i<m_BlockCoordinates.size(); i++)
    {
        /*Increment Y coordinate*/
        m_BlockCoordinates[i].second++;
    }

    Drawer::EraseBlock(m_BlockSquaresGraphicsRectItemPointers);
    m_BlockSquaresGraphicsRectItemPointers = Drawer::DrawBlock(GetBlockCoordinates(), GetColor());
}

void BlockBase::DropAndPlaceBlock(const PlacedBlocks& placedBlocks)
{
    while(!IsSquareOrBottomWallUnderBlock(placedBlocks))
    {
        DropBlockOneLevel();
    }
}

QVector<QPair<int, int> > BlockBase::GetBlockCoordinates() const
{
    return m_BlockCoordinates;
}
