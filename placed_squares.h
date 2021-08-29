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

    enum class SquarePresence
    {
        SQUARE_PRESENT, NO_SQUARE
    };

    void ClearPlacedBlocks();
    void AddSquare(const Coordinates& coordinates);
    void RemoveRow(int rowNumber);
    QVector<int> FindFullRows() const;
    void DropRowsAbove(int removedRow);
    const QMap<Coordinates, SquarePresence>& GetPlacedBlocksMap() const {return m_PlacedBlocksMap;}
    static const Qt::GlobalColor PLACED_SQUARES_COLOR = Qt::white;

private:
    /*Map storing bool value representing every square block*/
    QMap<Coordinates, SquarePresence> m_PlacedBlocksMap;

    void RemoveSquare(const Coordinates& coordinates);
};
