#ifndef PLACEDBLOCKS_H
#define PLACEDBLOCKS_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QMap>
#include <QPoint>
#include <QHash>
#include <QPair>
#include <QGraphicsRectItem>


class PlacedBlocks : public QObject
{
    Q_OBJECT
public:
    explicit PlacedBlocks(QObject *parent = nullptr);

    QMap<QPair<int,int>,QGraphicsRectItem*> placedBlocksArray; // PUBLIC!!

    void addSquare(int x, int y, QGraphicsRectItem* square_graphic_ptr);
    int findFullRows() const;
    void dropRowsAbove(int deletedRow);
    void deleteSquare(int x, int y);
    void deleteRow(int row_number);

private:

signals:

public slots:
};

#endif // PLACEDBLOCKS_H
