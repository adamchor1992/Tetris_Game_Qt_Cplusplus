#pragma once

#include <QDebug>
#include <QVector>
#include <QMap>
#include <QPair>
#include <QGraphicsRectItem>

class PlacedBlocks
{
public:
    explicit PlacedBlocks();

    enum class SquarePresence
    {
        SQUARE_PRESENT, NO_SQUARE
    };

    void ClearPlacedBlocks();
    void AddSquare(int x, int y);
    void RemoveRow(int rowNumber);
    QList<int> FindFullRows() const;
    void DropRowsAbove(int removedRow);
    const QMap<QPair<int, int>, SquarePresence>& GetPlacedBlocksMap() const {return m_PlacedBlocksMap;}

private:
    /*Map storing bool value representing every square block*/
    QMap<QPair<int,int>, SquarePresence> m_PlacedBlocksMap;

    void RemoveSquare(int x, int y);
};
