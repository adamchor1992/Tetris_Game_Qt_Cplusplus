#pragma once

#include "common.h"
#include "coordinates.h"

class Square
{
public:
    Square(const Coordinates& coordinates, const QColor& color);

    [[nodiscard]] const Coordinates& getCoordinates() const
    { return coordinates_; }

    void move(int x, int y);
    [[nodiscard]] const QColor& getColor() const {return COLOR;}

private:
    Coordinates coordinates_;
    const QColor COLOR;
};
