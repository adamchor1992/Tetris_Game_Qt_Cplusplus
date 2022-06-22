#include "square.h"

Square::Square(const Coordinates& coordinates, const QColor& color) :
        QGraphicsRectItem((coordinates.x - 1) * GameArenaParameters::blockSquareSize + GameArenaParameters::wallOffset,
                          (coordinates.y - 1) * GameArenaParameters::blockSquareSize + GameArenaParameters::wallOffset,
                          GameArenaParameters::blockSquareSize,
                          GameArenaParameters::blockSquareSize),
        coordinates_{coordinates}
{
    setPen(Qt::NoPen);
    setBrush(color);
    show();
}

void Square::move(int x, int y)
{
    coordinates_ += {x, y};
    moveBy(x * GameArenaParameters::blockSquareSize, y * GameArenaParameters::blockSquareSize);
}