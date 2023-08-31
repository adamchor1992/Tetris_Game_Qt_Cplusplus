#include "coordinates.h"
#include "config.h"

bool Coordinates::validateCoordinates(const Coordinates& coordinates)
{
    return (coordinates.x >= Config::Arena::MINIMUM_X) && (coordinates.x <= Config::Arena::MAXIMUM_X) && (coordinates.y >= Config::Arena::MINIMUM_Y) &&
           (coordinates.y <= Config::Arena::MAXIMUM_Y);
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

Coordinates Coordinates::operator+(const RotationCoefficients& rotationCoefficients) const
{
    return Coordinates{x + rotationCoefficients.getRotationCoefficients().first, y + rotationCoefficients.getRotationCoefficients().second};
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

Coordinates Coordinates::operator+(const std::pair<int, int>& coefficientsPair) const
{
    return {x + coefficientsPair.first, y + coefficientsPair.second};
}

std::ostream& operator<<(std::ostream& os, const Coordinates& coordinates)
{
    os << "[" << coordinates.x << "," << coordinates.y << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Coordinates>& coordinatesVector)
{
    for(const Coordinates& coordinates : coordinatesVector)
    {
        os << "[" << coordinates.x << "," << coordinates.y << "]";
    }

    return os;
}
