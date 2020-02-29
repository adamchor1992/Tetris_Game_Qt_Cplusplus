#pragma once

#include <QDebug>
#include <QVector>
#include <QMap>
#include <QPoint>
#include <QHash>
#include <QPair>
#include <QGraphicsRectItem>

class PlacedBlocks
{
public:
    explicit PlacedBlocks();
    void AddSquare(int x, int y, QGraphicsRectItem* p_SquareGraphicsItem);
    void DeleteRow(int rowNumber);
    int FindFullRow() const;
    void DropRowsAbove(int deletedRow);
    QMap<QPair<int, int>, QGraphicsRectItem*> const& GetPlacedBlocksMap() const {return m_PlacedBlocksMap;}

private:
    /*Map storing QGraphicsRectItem representing every square block*/
    QMap<QPair<int,int>,QGraphicsRectItem*> m_PlacedBlocksMap;

    bool ValidateCoordinates(int x, int y);
    void DeleteSquare(int x, int y);

    int const COLUMN_COUNT = 10;
    int const ROW_COUNT = 20;
};
