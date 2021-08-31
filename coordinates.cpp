#include "coordinates.h"
#include "utilities.h"
#include "placed_squares.h"

#include <stdexcept>
#include <QDebug>

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
