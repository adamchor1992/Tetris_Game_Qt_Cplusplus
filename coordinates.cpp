#include <stdexcept>
#include <QDebug>

#include "coordinates.h"
#include "utilities.h"
#include "placed_blocks.h"

Coordinates::Coordinates(int x, int y)
{
    if(ValidateCoordinates(x, y))
    {
        m_X = x;
        m_Y = y;
    }
    else
    {
        throw std::out_of_range("Error! Coordinates out of range");
    }
}

bool Coordinates::ValidateCoordinates(int x, int y)
{
    if((x >= GameArenaParameters::MIN_BLOCK_COLUMNS) && (x <= GameArenaParameters::MAX_BLOCK_COLUMNS) && (y >= GameArenaParameters::MIN_BLOCK_ROWS) && (y <= GameArenaParameters::MAX_BLOCK_ROWS))
    {
        return true;
    }
    else
    {
        qDebug("INVALID COORDINATES=(%d,%d)", x, y);
        return false;
    }
}

void Coordinates::Modify(int newX, int newY)
{
    m_X = newX;
    m_Y = newY;
}

bool Coordinates::CheckIfRotationIsPossible(const Coordinates& centralSquareCoordinates, const QVector<int>& rotationCoefficients, const PlacedBlocks& placedBlocks)
{
    int newCentralSquareX = centralSquareCoordinates.GetX();
    int newCentralSquareY = centralSquareCoordinates.GetY();

    int newSquare1X = centralSquareCoordinates.GetX() + rotationCoefficients.at(0);
    int newSquare1Y = centralSquareCoordinates.GetY() + rotationCoefficients.at(1);

    int newSquare2X = centralSquareCoordinates.GetX() + rotationCoefficients.at(2);
    int newSquare2Y = centralSquareCoordinates.GetY() + rotationCoefficients.at(3);

    int newSquare3X = centralSquareCoordinates.GetX() + rotationCoefficients.at(4);
    int newSquare3Y = centralSquareCoordinates.GetY() + rotationCoefficients.at(5);

    if(!ValidateCoordinates(newCentralSquareX, newCentralSquareY) ||
            !ValidateCoordinates(newSquare1X, newSquare1Y)||
            !ValidateCoordinates(newSquare2X, newSquare2Y)||
            !ValidateCoordinates(newSquare3X, newSquare3Y))
    {
        qDebug() << "WRONG COORDINATES IN CheckIfRotationIsPossible";
        return false;
    }

    const QVector<Coordinates> newCoordinates {Coordinates(newCentralSquareX, newCentralSquareY), Coordinates(newSquare1X, newSquare1Y), Coordinates(newSquare2X, newSquare2Y), Coordinates(newSquare3X, newSquare3Y)};

    if(!CheckForOverlappingSquares(newCoordinates, placedBlocks))
    {
        qDebug() << "OVERLAPPING SQUARES";
        return false;
    }

    return true;
}

bool Coordinates::CheckForOverlappingSquares(const QVector<Coordinates>& blockCoordinates, const PlacedBlocks& placedBlocks)
{
    for(auto& coordinates : blockCoordinates)
    {
        if(placedBlocks.GetPlacedBlocksMap().value(coordinates) == PlacedBlocks::SquarePresence::SQUARE_PRESENT)
        {
            return false;
        }
    }

    return true;
}

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    if(coordinates1.m_X < coordinates2.m_X)
    {
        return true;
    }
    else if(coordinates1.m_X > coordinates2.m_X)
    {
        return false;
    }
    else
    {
        if(coordinates1.m_Y < coordinates2.m_Y)
        {
            return true;
        }
        else if(coordinates1.m_Y > coordinates2.m_Y)
        {
            return false;
        }
        else
        {
            return false;
        }
    }
}
