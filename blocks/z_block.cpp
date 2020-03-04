#include "z_block.h"

ZBlock::ZBlock() : BlockBase()
{
    m_Square1PositionX = m_CentralSquareX - 1;
    m_Square1PositionY = m_CentralSquareY;
    m_Square2PositionX = m_CentralSquareX;
    m_Square2PositionY = m_CentralSquareY + 1;
    m_Square3PositionX = m_CentralSquareX + 1;
    m_Square3PositionY = m_CentralSquareY + 1;

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

void ZBlock::RotateBlock()
{
    m_CentralSquareX = m_BlockCoordinates.at(0).first;
    m_CentralSquareY = m_BlockCoordinates.at(0).second;

    if(m_CurrentRotation == 0)
    {
        int newCentralSquareX = m_CentralSquareX;
        int newCentralSquareY = m_CentralSquareY;
        int newSquare1X = m_CentralSquareX;
        int newSquare1Y = m_CentralSquareY - 1;
        int newSquare2X = m_CentralSquareX - 1;
        int newSquare2Y = m_CentralSquareY;
        int newSquare3X = m_CentralSquareX - 1;
        int newSquare3Y = m_CentralSquareY + 1;

        if(newSquare1X > 10 || newSquare1X < 1)
        {
            return;
        }
        if(newCentralSquareX > 10 || newCentralSquareX < 1)
        {
            return;
        }
        if(newSquare2X > 10 || newSquare2X < 1)
        {
            return;
        }
        if(newSquare3X > 10 || newSquare3X < 1)
        {
            return;
        }

        if(newSquare1Y > 20 || newSquare1Y < 1)
        {
            return;
        }
        if(newCentralSquareY > 20 || newCentralSquareY < 1)
        {
            return;
        }
        if(newSquare2Y > 20 || newSquare2Y < 1)
        {
            return;
        }
        if(newSquare3Y > 20 || newSquare3Y < 1)
        {
            return;
        }

        m_BlockCoordinates[0].first = newCentralSquareX;
        m_BlockCoordinates[0].second = newCentralSquareY;
        m_BlockCoordinates[1].first = newSquare1X;
        m_BlockCoordinates[1].second = newSquare1Y;
        m_BlockCoordinates[2].first = newSquare2X;
        m_BlockCoordinates[2].second = newSquare2Y;
        m_BlockCoordinates[3].first = newSquare3X;
        m_BlockCoordinates[3].second = newSquare3Y;

        m_CurrentRotation = 1;
    }
    else if(m_CurrentRotation == 1)
    {
        int newCentralSquareX = m_CentralSquareX;
        int newCentralSquareY = m_CentralSquareY;
        int newSquare1X = m_CentralSquareX - 1;
        int newSquare1Y = m_CentralSquareY;
        int newSquare2X = m_CentralSquareX;
        int newSquare2Y = m_CentralSquareY + 1;
        int newSquare3X = m_CentralSquareX + 1;
        int newSquare3Y = m_CentralSquareY + 1;

        if(newSquare1X > 10 || newSquare1X < 1)
        {
            return;
        }
        if(newCentralSquareX > 10 || newCentralSquareX < 1)
        {
            return;
        }
        if(newSquare2X > 10 || newSquare2X < 1)
        {
            return;
        }
        if(newSquare3X > 10 || newSquare3X < 1)
        {
            return;
        }

        if(newSquare1Y > 20 || newSquare1Y < 1)
        {
            return;
        }
        if(newCentralSquareY > 20 || newCentralSquareY < 1)
        {
            return;
        }
        if(newSquare2Y > 20 || newSquare2Y < 1)
        {
            return;
        }
        if(newSquare3Y > 20 || newSquare3Y < 1)
        {
            return;
        }

        m_BlockCoordinates[0].first = newCentralSquareX;
        m_BlockCoordinates[0].second = newCentralSquareY;
        m_BlockCoordinates[1].first = newSquare1X;
        m_BlockCoordinates[1].second = newSquare1Y;
        m_BlockCoordinates[2].first = newSquare2X;
        m_BlockCoordinates[2].second = newSquare2Y;
        m_BlockCoordinates[3].first = newSquare3X;
        m_BlockCoordinates[3].second = newSquare3Y;

        m_CurrentRotation = 0;
    }
}
