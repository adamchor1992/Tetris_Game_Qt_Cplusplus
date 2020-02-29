#include "block_base.h"

BlockBase::BlockBase(QString shape)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); //seed based on time

    int randomNumber = std::rand();

    m_BlockColor = m_Colors.at(randomNumber % m_Colors.size());

    m_CentralSquareX = 5;
    m_CentralSquareY = 1;

    if(shape == "S")
    {
        m_Square1PositionX = m_CentralSquareX - 1;
        m_Square1PositionY = m_CentralSquareY + 1;
        m_Square2PositionX = m_CentralSquareX;
        m_Square2PositionY = m_CentralSquareY + 1;
        m_Square3PositionX = m_CentralSquareX + 1;
        m_Square3PositionY = m_CentralSquareY;
    }
    else if(shape == "Z")
    {
        m_Square1PositionX = m_CentralSquareX - 1;
        m_Square1PositionY = m_CentralSquareY;
        m_Square2PositionX = m_CentralSquareX;
        m_Square2PositionY = m_CentralSquareY + 1;
        m_Square3PositionX = m_CentralSquareX + 1;
        m_Square3PositionY = m_CentralSquareY + 1;
    }
    else if(shape == "I")
    {
        m_Square1PositionX = m_CentralSquareX - 1;
        m_Square1PositionY = m_CentralSquareY;
        m_Square2PositionX = m_CentralSquareX + 1;
        m_Square2PositionY = m_CentralSquareY;
        m_Square3PositionX = m_CentralSquareX + 2;
        m_Square3PositionY = m_CentralSquareY;
    }
    else if(shape == "J")
    {
        m_Square1PositionX = m_CentralSquareX - 1;
        m_Square1PositionY = m_CentralSquareY;
        m_Square2PositionX = m_CentralSquareX + 1;
        m_Square2PositionY = m_CentralSquareY;
        m_Square3PositionX = m_CentralSquareX + 1;
        m_Square3PositionY = m_CentralSquareY + 1;
    }
    else if(shape == "L")
    {
        m_Square1PositionX = m_CentralSquareX - 1;
        m_Square1PositionY = m_CentralSquareY + 1;
        m_Square2PositionX = m_CentralSquareX - 1;
        m_Square2PositionY = m_CentralSquareY;
        m_Square3PositionX = m_CentralSquareX + 1;
        m_Square3PositionY = m_CentralSquareY;
    }
    else if(shape == "O")
    {
        m_Square1PositionX = m_CentralSquareX;
        m_Square1PositionY = m_CentralSquareY + 1;
        m_Square2PositionX = m_CentralSquareX + 1;
        m_Square2PositionY = m_CentralSquareY + 1;
        m_Square3PositionX = m_CentralSquareX + 1;
        m_Square3PositionY = m_CentralSquareY;
    }
    else if(shape == "T")
    {
        m_Square1PositionX = m_CentralSquareX - 1;
        m_Square1PositionY = m_CentralSquareY;
        m_Square2PositionX = m_CentralSquareX;
        m_Square2PositionY = m_CentralSquareY + 1;
        m_Square3PositionX = m_CentralSquareX + 1;
        m_Square3PositionY = m_CentralSquareY;
    }
    else
    {
        qDebug() << "UNKNOWN SHAPE, ABORTING";
        assert(false);
    }

    m_BlockCoordinates.append(m_Square1PositionX);
    m_BlockCoordinates.append(m_Square1PositionY);
    m_BlockCoordinates.append(m_CentralSquareX);
    m_BlockCoordinates.append(m_CentralSquareY);
    m_BlockCoordinates.append(m_Square2PositionX);
    m_BlockCoordinates.append(m_Square2PositionY);
    m_BlockCoordinates.append(m_Square3PositionX);
    m_BlockCoordinates.append(m_Square3PositionY);
}

BlockBase::~BlockBase()
{

}

void BlockBase::MoveBlock(Direction direction)
{
    if(direction == Direction::left)
    {
        for(int i=0; i < m_BlockCoordinates.size(); i=i+2)
        {
            int currentX = m_BlockCoordinates.at(i); //x coordinate
            int currentY = m_BlockCoordinates.at(i+1); //y coordinate

            int newX = currentX - 1; //x decreases
            int newY = currentY; //y does not change

            m_BlockCoordinates[i] = newX;
            m_BlockCoordinates[i+1] = newY;
        }
    }
    else if(direction == Direction::right)
    {
        for(int i=0; i < m_BlockCoordinates.size(); i=i+2)
        {
            int currentX = m_BlockCoordinates.at(i); //x coordinate
            int currentY = m_BlockCoordinates.at(i+1); //y coordinate

            int newX = currentX + 1; //x increases
            int newY = currentY; //y does not change

            m_BlockCoordinates[i] = newX;
            m_BlockCoordinates[i+1] = newY;
        }
    }
    else
    {
        qDebug() << "WRONG DIRECTION";
        assert(false);
    }
}

void BlockBase::RotateBlock()
{
    qDebug() << "BASE CLASS RotateBlock() METHOD CALLED";
    assert(false);
}

bool BlockBase::IsSquaresLeftOfBlock(PlacedBlocks const* p_PlacedBlocks)
{
    for(int i=0; i<m_BlockCoordinates.size(); i=i+2)
    {
        int currentX = m_BlockCoordinates.at(i); //x coordinate
        int currentY = m_BlockCoordinates.at(i+1); //y coordinate

        int leftBlockX = currentX - 1; // x is decreased
        int leftBlockY = currentY; // y does not change

        if(leftBlockX < 1) // if there is left wall next to the block
        {
            return true;
        }

        QPair<int,int> leftOfBlockCoordinatesPair(leftBlockX,leftBlockY);

        //check if there is any block to the left of current block
        if(p_PlacedBlocks->getPlacedBlocksMap().value(leftOfBlockCoordinatesPair) != nullptr)
        {
            return true;
        }
    }

    return false;
}

bool BlockBase::IsSquaresRightOfBlock(PlacedBlocks const* p_PlacedBlocks)
{
    for(int i=0; i<m_BlockCoordinates.size(); i=i+2)
    {
        int currentX = m_BlockCoordinates.at(i); //x coordinate
        int currentY = m_BlockCoordinates.at(i+1); //y coordinate

        int rightBlockX = currentX + 1; // x is increased
        int rightBlockY = currentY; // y does not change

        if(rightBlockX > 10) // if there is left wall next to the block
        {
            return true;
        }

        QPair<int,int> rightOfBlockCoordinatesPair(rightBlockX,rightBlockY);

        //check if there is any block to the right of current block
        if(p_PlacedBlocks->getPlacedBlocksMap().value(rightOfBlockCoordinatesPair) != nullptr)
        {
            return true;
        }
    }

    return false;
}

bool BlockBase::IsSquaresUnderBlock(PlacedBlocks const* p_PlacedBlocks)
{
    for(int i=0; i < m_BlockCoordinates.size(); i=i+2)
    {
        int currentX = m_BlockCoordinates.at(i); //x coordinate
        int currentY = m_BlockCoordinates.at(i+1); //y coordinate

        int belowBlockX = currentX; // x does not change
        int belowBlockY = currentY + 1; // y is increased

        if(belowBlockY > 20) // if there is bottom under block
        {
            return true;
        }

        QPair<int,int> belowBlockCoordinatesPair(belowBlockX,belowBlockY);

        //check if there is any block below current block
        if(p_PlacedBlocks->getPlacedBlocksMap().value(belowBlockCoordinatesPair) != nullptr)
        {
            return true;
        }
    }
    return false;
}

QColor BlockBase::GetColor()
{
    return m_BlockColor;
}

void BlockBase::DropBlockCoordinates()
{
    for(int i=1; i<m_BlockCoordinates.size(); i=i+2)
    {
        m_BlockCoordinates[i]++;
    }
}

QVector<int> BlockBase::GetBlockCoordinates()
{
    return m_BlockCoordinates;
}
