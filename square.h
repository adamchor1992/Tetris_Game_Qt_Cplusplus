#ifndef SQUARE_H
#define SQUARE_H

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QMap>
#include <QDebug>
#include <QHash>

class Square : public QObject
{
    Q_OBJECT
public:
    explicit Square(int x, int y, QObject *parent = nullptr);
//    Square();
//    Square(const Square&);
//    Square& operator=(const Square&);

    void fillPossibleSquarePositions();

    int getX() {return x_coordinate;}
    int getY() {return y_coordinate;}

    QVector<QPoint> getPossibleSquarePositions_XY() {return possibleSquarePositions_XY;}
    QVector<QPoint> getPossibleSquarePositions_Paint() {return possibleSquarePositions_Paint;}

    bool isMovePossible(int x, int y);

private:
    int x_coordinate;
    int y_coordinate;
    //QColor color; // some color

    QVector<QPoint> possibleSquarePositions_XY;
    QVector<QPoint> possibleSquarePositions_Paint;

signals:

public slots:
};

#endif // SQUARE_H
