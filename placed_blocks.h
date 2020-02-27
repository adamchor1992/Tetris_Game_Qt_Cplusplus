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
    int FindFullRows() const;
    void DropRowsAbove(int deletedRow);
    void DeleteSquare(int x, int y);
    void DeleteRow(int rowNumber);

    QMap<QPair<int,int>,QGraphicsRectItem*> m_PlacedBlocksArray;
};
