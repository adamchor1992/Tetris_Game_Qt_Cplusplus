#include "square.h"

Square::Square(QObject *parent) : QObject(parent)
{
    fillPossibleSquarePositions();
}

void Square::fillPossibleSquarePositions()
{
    for(int j = 1, y = 1; j<=20; j++, y++)
    {
        for(int i = 1, x = 1; i<=10; i++, x++) //rows
        {
            possibleSquarePositions_XY.append(QPoint(i,j));
            possibleSquarePositions_Paint.append(QPoint(6+(i-1)*29,(j-1)*29));
        }
    }
}
