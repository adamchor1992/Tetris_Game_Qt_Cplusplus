#pragma once

#include "coordinates.h"
#include "square.h"
#include <map>

using CoordinatesToSquaresMapping = std::map<Coordinates, Square>;

class Block;

class PlacedSquares
{
public:
    [[nodiscard]] std::vector<int> findFullRowsNumbers() const;
    void addSquare(const Coordinates& squareCoordinates, const QColor& color);
    void removeRow(int rowNumber);
    void dropRowsAboveGivenRow(int removedRow);
    void placeBlock(Block& block);

    [[nodiscard]] bool isFieldOccupied(const Coordinates& coordinates) const;

    [[nodiscard]] const CoordinatesToSquaresMapping& getCoordinatesToSquaresMapping() const
    { return coordinatesToSquaresMapping_; }

private:
    void removeSquare(const Coordinates& coordinates);

    CoordinatesToSquaresMapping coordinatesToSquaresMapping_;
};
