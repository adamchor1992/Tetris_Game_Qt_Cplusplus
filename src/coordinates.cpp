#include "coordinates.h"
#include "common.h"

bool Coordinates::validateCoordinates(const Coordinates& coordinates)
{
    return (coordinates.x >= GameArenaParameters::minBlockColumns) && (coordinates.x <= GameArenaParameters::maxBlockColumns) && (coordinates.y >= GameArenaParameters::minBlockRows) && (coordinates.y <= GameArenaParameters::maxBlockRows);
}

bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    return (coordinates1.x == coordinates2.x) && (coordinates1.y == coordinates2.y);
}

bool operator!=(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    return !(coordinates1 == coordinates2);
}

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    if(coordinates1.x < coordinates2.x)
    {
        return true;
    }
    else if(coordinates1.x > coordinates2.x)
    {
        return false;
    }
    else
    {
        return coordinates1.y < coordinates2.y;
    }
}

void Coordinates::operator+=(const Coordinates& coordinates)
{
    x += coordinates.x;
    y += coordinates.y;
}

Coordinates Coordinates::operator-(const Coordinates& coordinates) const
{
    return {x - coordinates.x, y - coordinates.y};
}

Coordinates Coordinates::operator+(const RotationCoefficients& rotationCoefficients) const
{
    return {x + rotationCoefficients.x, y + rotationCoefficients.y};
}

Coordinates Coordinates::operator+(const TransformationCoefficients& transformationCoefficients) const
{
    return {x + transformationCoefficients.x, y + transformationCoefficients.y};
}