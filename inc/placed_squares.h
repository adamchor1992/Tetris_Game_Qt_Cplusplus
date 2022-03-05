#pragma once

#include "coordinates.h"

#include <QVector>
#include <QMap>
#include <QGraphicsRectItem>
#include <QColor>

class PlacedSquares
{
public:
    explicit PlacedSquares();
    [[nodiscard]] const QMap<Coordinates, QGraphicsRectItem*>& getCoordinatesToSquaresMapping() const {return coordinatesToSquaresMapping_;}
    QMap<Coordinates, QGraphicsRectItem*>& getCoordinatesToSquaresMapping() {return coordinatesToSquaresMapping_;}
    void removeAllPlacedSquares();
    [[nodiscard]] QVector<int> findFullRows() const;
    void removeFullRow(int rowNumber);
    void dropRowsAbove(int removedRow);
    void addSquare(const Coordinates& coordinates, QColor color, PlacedSquares& placedSquares);

    static const Qt::GlobalColor placedSquares_color = Qt::white;

private:
    void removeSquare(const Coordinates& coordinates);

    QMap<Coordinates, QGraphicsRectItem*> coordinatesToSquaresMapping_;
};
