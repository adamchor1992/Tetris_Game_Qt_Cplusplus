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
    const QMap<Coordinates, QGraphicsRectItem*>& getPlacedSquaresMap() const {return placedSquaresMap_;}
    QMap<Coordinates, QGraphicsRectItem*>& getPlacedSquaresMap() {return placedSquaresMap_;}
    void removeAllPlacedSquares();
    QVector<int> findFullRows() const;
    void removeFullRow(int rowNumber);
    void dropRowsAbove(int removedRow);
    void addSquare(const Coordinates& coordinates, QColor color, PlacedSquares& placedSquares);

    static const Qt::GlobalColor placedSquares_color_ = Qt::white;

private:
    void removeSquare(const Coordinates& coordinates);

    QMap<Coordinates, QGraphicsRectItem*> placedSquaresMap_;
};
