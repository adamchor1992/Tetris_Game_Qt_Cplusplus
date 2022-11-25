#include "coordinates.h"
#include "common.h"

bool Coordinates::validateCoordinates(const Coordinates& coordinates)
{
    return (coordinates.x >= GameParameters::Arena::minBlockColumns) && (coordinates.x <= GameParameters::Arena::maxBlockColumns) && (coordinates.y >= GameParameters::Arena::minBlockRows) && (coordinates.y <= GameParameters::Arena::maxBlockRows);
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

Coordinates Coordinates::operator+(const std::pair<int, int>& coefficientsPair) const
{
    return {x + coefficientsPair.first, y + coefficientsPair.second};
}

std::ostream& operator<<(std::ostream& os, const Coordinates& coordinates)
{
    os << "[" << coordinates.x << "," << coordinates.y << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const QVector<Coordinates>& coordinatesVector)
{
    for(const Coordinates& coordinates : coordinatesVector)
    {
        os << "[" << coordinates.x << "," << coordinates.y << "]";
    }

    return os;
}
