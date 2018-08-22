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
    explicit Square(QObject *parent = nullptr);
    void fillPossibleSquarePositions();

    QVector<QPoint> getPossibleSquarePositions_XY() {return possibleSquarePositions_XY;}
    QVector<QPoint> getPossibleSquarePositions_Paint() {return possibleSquarePositions_Paint;}

private:
    QVector<QPoint> possibleSquarePositions_XY;
    QVector<QPoint> possibleSquarePositions_Paint;

signals:

public slots:
};

#endif // SQUARE_H
