#include "square.h"

Square::Square(int x, int y, QObject *parent) : QObject(parent)
{
    x_coordinate = x;
    y_coordinate = y;

    fillPossibleSquarePositions();
}

//Square::Square()
//{
//     qDebug() << "GOWNO3";
//}

//Square::Square(const Square &)
//{
//    qDebug() << "GOWNO";
//}

//Square& Square::Square::operator=(const Square &)
//{
//    qDebug() << "GOWNO2";
//}

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

bool Square::isMovePossible(int x, int y)
{
    QPoint new_coordinates(x,y);

    if(possibleSquarePositions_XY.contains(new_coordinates))
        return true;
    else
        return false;
}
