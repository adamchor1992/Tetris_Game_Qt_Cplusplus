#include "square.h"

Square::Square(const Coordinates& coordinates, const QColor& color) : coordinates_{coordinates}, COLOR(color)
{

}

void Square::move(int x, int y)
{
    coordinates_ += {x, y};
}
