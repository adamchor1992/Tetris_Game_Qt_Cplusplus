#pragma once

#include <QPair>
#include <QVector>

class PlacedBlocks;

class Coordinates
{
    friend bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);

public:
    Coordinates(int x, int y);
    Coordinates(const Coordinates&) = default;
    Coordinates(Coordinates&&) = default;
    Coordinates& operator=(const Coordinates&) = delete;
    Coordinates& operator=(const Coordinates&&) = delete;

    void Modify(int newX, int newY);
    int GetX() const {return m_X;}
    int GetY() const {return m_Y;}

    static bool ValidateCoordinates(int x, int y);
    static bool CheckIfRotationIsPossible(const Coordinates& centralSquareCoordinates, const QVector<int>& rotationCoefficients, const PlacedBlocks& placedBlocks);
    static bool CheckForOverlappingSquares(const QVector<Coordinates>& blockCoordinates, const PlacedBlocks& placedBlocks);

private:
    int m_X;
    int m_Y;
};

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);
