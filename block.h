#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "placedblocks.h"

class Block : public QObject
{
    Q_OBJECT
public:
    explicit Block(QString _shape = "I", QObject *parent = nullptr);

    void moveBlock(int direction);
    QVector<int> getBlockCoordinates();

    bool isSquaresLeftOfBlock(const PlacedBlocks *placed_blocks);
    bool isSquaresRightOfBlock(const PlacedBlocks *placed_blocks);
    bool isSquaresUnderBlock(const PlacedBlocks *placed_blocks);

    void setBlockPresentOnScreen(bool present);
    bool isBlockPresentOnScreen() {return blockIsPresentOnScreen;}

    QColor getColor();

    virtual void rotateBlock() = 0; //pure virtual

    virtual ~Block();

protected:
    QString shape;

    int central_square_x = 0;
    int central_square_y = 0;
    int square1posx = 0;
    int square1posy = 0;
    int square2posx = 0;
    int square2posy = 0;
    int square3posx = 0;
    int square3posy = 0;

    QVector<int> blockCoordinates;
    QVector<QGraphicsRectItem*> block_graphics_items_ptrs;

private:
    QVector<QGraphicsRectItem*> graphicalPointersVector;
    bool blockIsPresentOnScreen;
    QVector<QColor> colors = {Qt::red, Qt::blue, Qt::white, Qt::green, Qt::yellow, Qt::cyan, Qt::magenta};
    QColor blockColor;

signals:

public slots:
    void dropBlockCoordinates();
};

#endif // BLOCK_H
