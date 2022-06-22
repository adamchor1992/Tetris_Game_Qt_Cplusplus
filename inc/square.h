#pragma once

#include "common.h"
#include "coordinates.h"

#include <QGraphicsRectItem>
#include <QPen>

class Square : public QGraphicsRectItem
{
public:
    Square(const Coordinates& coordinates, const QColor& color);
    [[nodiscard]] Coordinates& getCoordinates() {return coordinates_;}
    void move(int x, int y);

private:
    Coordinates coordinates_;
};
