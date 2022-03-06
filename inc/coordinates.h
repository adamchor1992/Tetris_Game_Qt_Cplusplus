#pragma once

#include <QVector>

class PlacedSquares;

class Coordinates
{
    friend bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);

public:
    Coordinates(int x, int y);
    Coordinates(const Coordinates&) = default;
    Coordinates(Coordinates&&) = default;
    Coordinates& operator=(const Coordinates&) = delete;
    Coordinates& operator=(const Coordinates&&) = delete;

    static bool validateCoordinates(int x, int y);

    [[nodiscard]] int getX() const {return x_;}
    [[nodiscard]] int getY() const {return y_;}

    void modify(int newX, int newY);

private:
    int x_;
    int y_;
};

bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator!=(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);
