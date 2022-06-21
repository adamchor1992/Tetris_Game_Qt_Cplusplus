#include "placed_squares.h"
#include "drawer.h"
#include "common.h"

PlacedSquares::~PlacedSquares()
{
    removeAllPlacedSquares();
}

void PlacedSquares::removeAllPlacedSquares()
{
    for(QGraphicsRectItem* square : coordinatesToSquaresMapping_)
    {
        Drawer::eraseSquare(square);
    }

    coordinatesToSquaresMapping_.clear();
}

void PlacedSquares::stealSquaresFromBlock(const QVector<Coordinates>& blockCoordinates, QVector<QGraphicsRectItem*>& squaresGraphicsRectItems, PlacedSquares& placedSquares)
{
    for (int i = 0; i < blockCoordinates.size(); ++i)
    {
        const Coordinates& coordinates = blockCoordinates.at(i);

        if(!coordinatesToSquaresMapping_.contains(coordinates))
        {
            coordinatesToSquaresMapping_[coordinates] = squaresGraphicsRectItems.at(i);
            squaresGraphicsRectItems[i] = nullptr;
        }
        else
        {
            throw std::runtime_error("Placing square on non-empty field");
        }
    }
}

void PlacedSquares::removeSquare(const Coordinates& coordinates)
{
    if(coordinatesToSquaresMapping_.contains(coordinates))
    {
        Drawer::eraseSquare(coordinates, *this);
    }
    else
    {
        throw std::runtime_error("Removing square from already empty field");
    }
}

void PlacedSquares::removeFullRow(int rowNumber)
{
    const int& y = rowNumber;

    if(y < GameArenaParameters::minBlockRows || y > GameArenaParameters::maxBlockRows)
    {
        throw std::runtime_error("Wrong row number");
    }

    for(int x = GameArenaParameters::minBlockColumns; x <= GameArenaParameters::maxBlockColumns; x++)
    {
        removeSquare(Coordinates{x, y});
    }
}

QVector<int> PlacedSquares::findFullRows() const
{
    QVector<int> fullRows;

    /*Go through all rows*/
    for(int row = 1; row <= GameArenaParameters::maxBlockRows; ++row)
    {
        for(int column = 1; column <= GameArenaParameters::maxBlockColumns; ++column)
        {
            if(!coordinatesToSquaresMapping_.contains(Coordinates{column, row}))
            {
                break;
            }

            if(column == GameArenaParameters::maxBlockColumns)
            {
                fullRows.append(row);
            }
        }
    }

    if(fullRows.size() > 4)
    {
        throw std::runtime_error("Wrong full rows count");
    }

    return fullRows;
}

/*Drop all rows above deleted row*/
void PlacedSquares::dropRowsAbove(int removedRow)
{
    Drawer::dropRow(removedRow, *this);

    /*Drop all rows by one*/
    for(int x = GameArenaParameters::minBlockColumns; x <= GameArenaParameters::maxBlockColumns; x++)
    {
        for(int y = removedRow - 1; y > GameArenaParameters::minBlockRows; --y)
        {
            Coordinates coordinates{x, y};
            Coordinates coordinatesOneRowBelow{x, y + 1};

            if(coordinatesToSquaresMapping_.contains(coordinates))
            {
                coordinatesToSquaresMapping_.insert(coordinatesOneRowBelow, coordinatesToSquaresMapping_.value(coordinates));
                coordinatesToSquaresMapping_.remove(coordinates);
            }
        }
    }
}
