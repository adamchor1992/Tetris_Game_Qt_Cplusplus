#pragma once

#include "coordinates.h"

#include <QVector>
#include <QMap>
#include <QGraphicsRectItem>
#include <QColor>

class PlacedSquares
{
public:
    static const Qt::GlobalColor PLACED_SQUARES_COLOR = Qt::white;

    explicit PlacedSquares();
    const QMap<Coordinates, QGraphicsRectItem*>& GetPlacedSquaresMap() const {return m_PlacedSquaresMap;}
    QMap<Coordinates, QGraphicsRectItem*>& GetPlacedSquaresMap() {return m_PlacedSquaresMap;}
    void RemoveAllPlacedSquares();
    QVector<int> FindFullRows() const;
    void RemoveFullRow(int rowNumber);
    void DropRowsAbove(int removedRow);
    void AddSquare(const Coordinates& coordinates, QColor color, PlacedSquares& placedSquares);

private:
    QMap<Coordinates, QGraphicsRectItem*> m_PlacedSquaresMap;
    void RemoveSquare(const Coordinates& coordinates);
};
