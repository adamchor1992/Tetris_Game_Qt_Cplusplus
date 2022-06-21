#pragma once

#include "coordinates.h"

#include <QVector>
#include <QMap>
#include <QGraphicsRectItem>
#include <QColor>

using CoordinatesToSquaresMapping = QMap<Coordinates, QGraphicsRectItem*>;

class PlacedSquares
{
public:
    PlacedSquares() = default;
    ~PlacedSquares();

    [[nodiscard]] const CoordinatesToSquaresMapping& getCoordinatesToSquaresMapping() const {return coordinatesToSquaresMapping_;}
    CoordinatesToSquaresMapping& getCoordinatesToSquaresMapping() {return coordinatesToSquaresMapping_;}
    void removeAllPlacedSquares();
    [[nodiscard]] QVector<int> findFullRows() const;
    void removeFullRow(int rowNumber);
    void dropRowsAbove(int removedRow);
    void stealSquaresFromBlock(const QVector<Coordinates>& blockCoordinates, QVector<QGraphicsRectItem*>& squaresGraphicsRectItems, PlacedSquares& placedSquares);

private:
    void removeSquare(const Coordinates& coordinates);

    CoordinatesToSquaresMapping coordinatesToSquaresMapping_;
};
