#include "coordinates.h"
#include "common.h"

#include <stdexcept>

Coordinates::Coordinates(int x, int y)
{
    if(validateCoordinates(x, y))
    {
        x_ = x;
        y_ = y;
    }
    else
    {
        throw std::out_of_range("Error! Coordinates out of range");
    }
}

bool Coordinates::validateCoordinates(int x, int y)
{
    if((x >= GameArenaParameters::minBlockColumns) && (x <= GameArenaParameters::maxBlockColumns) && (y >= GameArenaParameters::minBlockRows) && (y <= GameArenaParameters::maxBlockRows))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Coordinates::modify(int newX, int newY)
{
    x_ = newX;
    y_ = newY;
}

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    if(coordinates1.x_ < coordinates2.x_)
    {
        return true;
    }
    else if(coordinates1.x_ > coordinates2.x_)
    {
        return false;
    }
    else
    {
        if(coordinates1.y_ < coordinates2.y_)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
