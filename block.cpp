#include "block.h"

Block::Block(QString shape)
{
    m_Shape = shape;
    m_CentralSquareX = 5;
    m_CentralSquareY = 1;

    std::srand(static_cast<unsigned int>(std::time(nullptr))); //seed based on time
    m_BlockColor = m_Colors.at(std::rand() % m_Colors.size());

    if(m_Shape == "S")
    {
        m_Square1PositionX = m_CentralSquareX - 1;
        m_Square1PositionY = m_CentralSquareY + 1;
        m_Square2PositionX = m_CentralSquareX;
        m_Square2PositionY = m_CentralSquareY + 1;
        m_Square3PositionX = m_CentralSquareX + 1;
        m_Square3PositionY = m_CentralSquareY;
    }
    else if(m_Shape == "Z")
    {
        m_Square1PositionX = m_CentralSquareX - 1;
        m_Square1PositionY = m_CentralSquareY;
        m_Square2PositionX = m_CentralSquareX;
        m_Square2PositionY = m_CentralSquareY + 1;
        m_Square3PositionX = m_CentralSquareX + 1;
        m_Square3PositionY = m_CentralSquareY + 1;
    }
    else if(m_Shape == "I")
    {
        m_Square1PositionX = m_CentralSquareX - 1;
        m_Square1PositionY = m_CentralSquareY;
        m_Square2PositionX = m_CentralSquareX + 1;
        m_Square2PositionY = m_CentralSquareY;
        m_Square3PositionX = m_CentralSquareX + 2;
        m_Square3PositionY = m_CentralSquareY;
    }
    else if(m_Shape == "J")
    {
        m_Square1PositionX = m_CentralSquareX - 1;
        m_Square1PositionY = m_CentralSquareY;
        m_Square2PositionX = m_CentralSquareX + 1;
        m_Square2PositionY = m_CentralSquareY;
        m_Square3PositionX = m_CentralSquareX + 1;
        m_Square3PositionY = m_CentralSquareY + 1;
    }
    else if(m_Shape == "L")
    {
        m_Square1PositionX = m_CentralSquareX - 1;
        m_Square1PositionY = m_CentralSquareY + 1;
        m_Square2PositionX = m_CentralSquareX - 1;
        m_Square2PositionY = m_CentralSquareY;
        m_Square3PositionX = m_CentralSquareX + 1;
        m_Square3PositionY = m_CentralSquareY;
    }
    else if(m_Shape == "O")
    {
        m_Square1PositionX = m_CentralSquareX;
        m_Square1PositionY = m_CentralSquareY + 1;
        m_Square2PositionX = m_CentralSquareX + 1;
        m_Square2PositionY = m_CentralSquareY + 1;
        m_Square3PositionX = m_CentralSquareX + 1;
        m_Square3PositionY = m_CentralSquareY;
    }
    else if(m_Shape == "T")
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
        return;
    }

    //pozycje są napisane w intach

    m_BlockCoordinates.append(m_Square1PositionX);
    m_BlockCoordinates.append(m_Square1PositionY);
    m_BlockCoordinates.append(m_CentralSquareX);
    m_BlockCoordinates.append(m_CentralSquareY);
    m_BlockCoordinates.append(m_Square2PositionX);
    m_BlockCoordinates.append(m_Square2PositionY);
    m_BlockCoordinates.append(m_Square3PositionX);
    m_BlockCoordinates.append(m_Square3PositionY);
}

Block::~Block()
{

}

void Block::MoveBlock(int direction)
{
    //direction 0 is left, 1 is right
    //block has 4 pairs of coordinates {1,1,2,2,3,3,4,4}

    if(direction == 0) // move to the left
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
    else if(direction == 1) // move to the right
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
    else //wrong direction
    {
        qDebug() << "WRONG DIRECTION";
    }
}

void Block::RotateBlock()
{
    qDebug() << "BASE CLASS RotateBlock() METHOD CALLED";
}

bool Block::IsSquaresLeftOfBlock(PlacedBlocks const* p_PlacedBlocks)
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
        if(p_PlacedBlocks->m_PlacedBlocksArray.value(leftOfBlockCoordinatesPair) != nullptr)
        {
            return true;
        }
    }

    return false;
}

bool Block::IsSquaresRightOfBlock(PlacedBlocks const* p_PlacedBlocks)
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
        if(p_PlacedBlocks->m_PlacedBlocksArray.value(rightOfBlockCoordinatesPair) != nullptr)
        {
            return true;
        }
    }

    return false;
}

bool Block::IsSquaresUnderBlock(PlacedBlocks const* p_PlacedBlocks)
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
        if(p_PlacedBlocks->m_PlacedBlocksArray.value(belowBlockCoordinatesPair) != nullptr)
        {
            return true;
        }
    }
    return false;
}

QColor Block::GetColor()
{
    return m_BlockColor;
}

void Block::DropBlockCoordinates()
{
    for(int i=1; i<m_BlockCoordinates.size(); i=i+2)
    {
        m_BlockCoordinates[i]++;
    }
}

QVector<int> Block::GetBlockCoordinates()
{
    return m_BlockCoordinates;
}
