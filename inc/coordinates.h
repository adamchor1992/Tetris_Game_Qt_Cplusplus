#pragma once

#include "coefficients.h"

#include <QVector>

struct Coordinates
{
    static bool validateCoordinates(const Coordinates& coordinates);

    void operator+=(const Coordinates& coordinates);
    Coordinates operator-(const Coordinates& coordinates) const;
    Coordinates operator+(const std::pair<int, int>& coefficientsPair) const;

    int x;
    int y;
};

bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator!=(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);
