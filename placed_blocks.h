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
    QMap<QPair<int, int>, QGraphicsRectItem*> const& getPlacedBlocksArray() const {return m_PlacedBlocksArray;}
    int FindFullRows() const;
    void DropRowsAbove(int deletedRow);
    void DeleteRow(int rowNumber);

private:
    QMap<QPair<int,int>,QGraphicsRectItem*> m_PlacedBlocksArray;

    void DeleteSquare(int x, int y);
};
