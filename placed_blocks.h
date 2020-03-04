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
    void ClearPlacedBlocks();
    void AddSquare(int x, int y, QGraphicsRectItem* p_SquareGraphicsItem);
    void RemoveRow(int rowNumber);
    QList<int> FindFullRows() const;
    void DropRowsAbove(int removedRow);
    QMap<QPair<int, int>, QGraphicsRectItem*> const& GetPlacedBlocksMap() const {return m_PlacedBlocksMap;}

private:
    /*Map storing QGraphicsRectItem representing every square block*/
    QMap<QPair<int,int>,QGraphicsRectItem*> m_PlacedBlocksMap;

    void RemoveSquare(int x, int y);

    int const COLUMN_COUNT = 10;
    int const ROW_COUNT = 20;
};
