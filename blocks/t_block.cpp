#include "t_block.h"
#include "drawer.h"

TBlock::TBlock() : BlockBase()
{
    m_Square1PositionX = m_CentralSquareX - 1;
    m_Square1PositionY = m_CentralSquareY;
    m_Square2PositionX = m_CentralSquareX;
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

void TBlock::RotateBlock(PlacedBlocks const& placedBlocks)
{
    m_CentralSquareX = m_BlockCoordinates.at(0).first;
    m_CentralSquareY = m_BlockCoordinates.at(0).second;

    int newCentralSquareX = 0;
    int newCentralSquareY = 0;
    int newSquare1X = 0;
    int newSquare1Y = 0;
    int newSquare2X = 0;
    int newSquare2Y = 0;
    int newSquare3X = 0;
    int newSquare3Y = 0;

    if(m_CurrentRotation == 0)
    {
        newCentralSquareX = m_CentralSquareX;
        newCentralSquareY = m_CentralSquareY;
        newSquare1X = m_CentralSquareX;
        newSquare1Y = m_CentralSquareY - 1;
        newSquare2X = m_CentralSquareX - 1;
        newSquare2Y = m_CentralSquareY;
        newSquare3X = m_CentralSquareX;
        newSquare3Y = m_CentralSquareY + 1;

        m_CurrentRotation = 1;
    }
    else if(m_CurrentRotation == 1)
    {
        newCentralSquareX = m_CentralSquareX;
        newCentralSquareY = m_CentralSquareY;
        newSquare1X = m_CentralSquareX + 1;
        newSquare1Y = m_CentralSquareY;
        newSquare2X = m_CentralSquareX;
        newSquare2Y = m_CentralSquareY - 1;
        newSquare3X = m_CentralSquareX - 1;
        newSquare3Y = m_CentralSquareY;

        m_CurrentRotation = 2;
    }
    else if(m_CurrentRotation == 2)
    {
        newCentralSquareX = m_CentralSquareX;
        newCentralSquareY = m_CentralSquareY;
        newSquare1X = m_CentralSquareX;
        newSquare1Y = m_CentralSquareY + 1;
        newSquare2X = m_CentralSquareX + 1;
        newSquare2Y = m_CentralSquareY;
        newSquare3X = m_CentralSquareX;
        newSquare3Y = m_CentralSquareY - 1;

        m_CurrentRotation = 3;
    }
    else if(m_CurrentRotation == 3)
    {
        newCentralSquareX = m_CentralSquareX;
        newCentralSquareY = m_CentralSquareY;
        newSquare1X = m_CentralSquareX - 1;
        newSquare1Y = m_CentralSquareY;
        newSquare2X = m_CentralSquareX;
        newSquare2Y = m_CentralSquareY + 1;
        newSquare3X = m_CentralSquareX + 1;
        newSquare3Y = m_CentralSquareY;

        m_CurrentRotation = 0;
    }

    QPair<int, int> newCentralSquareCoordinates(newCentralSquareX, newCentralSquareY);
    QPair<int, int> newSquare1Coordinates(newSquare1X, newSquare1Y);
    QPair<int, int> newSquare2Coordinates(newSquare2X, newSquare2Y);
    QPair<int, int> newSquare3Coordinates(newSquare3X, newSquare3Y);

    QVector<QPair<int, int> > newCoordinates;

    newCoordinates.append(newCentralSquareCoordinates);
    newCoordinates.append(newSquare1Coordinates);
    newCoordinates.append(newSquare2Coordinates);
    newCoordinates.append(newSquare3Coordinates);

    if(Drawer::ValidateCoordinates(newCoordinates))
    {
        for(auto coordinatesPair : newCoordinates)
        {
            if(placedBlocks.GetPlacedBlocksMap().value(coordinatesPair) != nullptr)
            {
                return;
            }
        }

        m_BlockCoordinates[0].first = newCentralSquareX;
        m_BlockCoordinates[0].second = newCentralSquareY;
        m_BlockCoordinates[1].first = newSquare1X;
        m_BlockCoordinates[1].second = newSquare1Y;
        m_BlockCoordinates[2].first = newSquare2X;
        m_BlockCoordinates[2].second = newSquare2Y;
        m_BlockCoordinates[3].first = newSquare3X;
        m_BlockCoordinates[3].second = newSquare3Y;
    }
}
