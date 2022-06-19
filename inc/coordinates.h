#pragma once

#include <QVector>

struct TransformationCoefficients
{
    int x;
    int y;
};

struct RotationCoefficients
{
    int x;
    int y;
};

struct Coordinates
{
    static bool validateCoordinates(const Coordinates& coordinates);

    void operator+=(const Coordinates& coordinates);
    Coordinates operator-(const Coordinates& coordinates) const;
    Coordinates operator+(const RotationCoefficients& rotationCoefficients) const;
    Coordinates operator+(const TransformationCoefficients& transformationCoefficients) const;

    int x;
    int y;
};

bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator!=(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);
