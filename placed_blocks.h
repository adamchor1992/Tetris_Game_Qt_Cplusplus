#pragma once

#include <QDebug>
#include <QVector>
#include <QMap>
#include <QGraphicsRectItem>

#include "coordinates.h"

class PlacedBlocks
{
public:
    explicit PlacedBlocks();

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

private:
    /*Map storing bool value representing every square block*/
    QMap<Coordinates, SquarePresence> m_PlacedBlocksMap;

    void RemoveSquare(const Coordinates& coordinates);
};
