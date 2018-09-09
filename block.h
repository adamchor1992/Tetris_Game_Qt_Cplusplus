#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "square.h"
#include "placedblocks.h"

class Block : public QObject
{
    Q_OBJECT
public:
    explicit Block(QString _shape = "S", QObject *parent = nullptr);
    int getLowestBlockPosition() {return lowestBlockPosition;}

    //void dropBlock();
    void moveBlock(int direction);
    void rotateBlock();

    QVector<int> getBlockCoordinates();
    bool isSquaresLeftOfBlock(const PlacedBlocks *placed_blocks);
    bool isSquaresRightOfBlock(const PlacedBlocks *placed_blocks);
    bool isSquaresUnderBlock(const PlacedBlocks *placed_blocks);

private:
    QString shape;
    int lowestBlockPosition;
    QVector<Square*> blockSquares;
    int central_square_x;
    int central_square_y;
    Square *centralsquare;
    Square *square1;
    Square *square2;
    Square *square3;
    QVector<int> blockCoordinates;

signals:

public slots:
    void dropBlockCoordinates();
};

#endif // BLOCK_H
