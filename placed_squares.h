#pragma once

#include <QDebug>
#include <QVector>
#include <QMap>
#include <QGraphicsRectItem>
#include <QColor>

#include "coordinates.h"

class PlacedSquares
{
public:
    explicit PlacedSquares();

    void RemoveAllPlacedSquares();
    void AddSquare(const Coordinates& coordinates, QColor color, PlacedSquares& placedSquares);
    void RemoveFullRow(int rowNumber);
    QVector<int> FindFullRows() const;
    void DropRowsAbove(int removedRow);
    const QMap<Coordinates, QGraphicsRectItem*>& GetPlacedSquaresMap() const {return m_PlacedSquaresMap;}
    QMap<Coordinates, QGraphicsRectItem*>& GetPlacedSquaresMap() {return m_PlacedSquaresMap;}
    static const Qt::GlobalColor PLACED_SQUARES_COLOR = Qt::white;

private:
    /*Map storing bool value representing every square block*/
    QMap<Coordinates, QGraphicsRectItem*> m_PlacedSquaresMap;

    void RemoveSquare(const Coordinates& coordinates);
};
