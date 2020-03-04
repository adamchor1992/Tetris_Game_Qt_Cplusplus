#include "o_block.h"

OBlock::OBlock() : BlockBase()
{
    m_Square1PositionX = m_CentralSquareX;
    m_Square1PositionY = m_CentralSquareY + 1;
    m_Square2PositionX = m_CentralSquareX + 1;
    m_Square2PositionY = m_CentralSquareY + 1;
    m_Square3PositionX = m_CentralSquareX + 1;
    m_Square3PositionY = m_CentralSquareY;

    m_CurrentRotation = 0;

    QPair<int, int> centralSquareCoordinates(m_CentralSquareX, m_CentralSquareY);
    QPair<int, int> square1Coordinates(m_Square1PositionX, m_Square1PositionY);
    QPair<int, int> square2Coordinates(m_Square2PositionX, m_Square2PositionY);
    QPair<int, int> square3Coordinates(m_Square3PositionX, m_Square3PositionY);

    m_BlockCoordinates.append(centralSquareCoordinates);
    m_BlockCoordinates.append(square1Coordinates);
    m_BlockCoordinates.append(square2Coordinates);
    m_BlockCoordinates.append(square3Coordinates);
}

void OBlock::RotateBlock(PlacedBlocks const& placedBlocks)
{
    /*This block does not rotate*/
}
