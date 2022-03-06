#include "placed_squares.h"
#include "drawer.h"
#include "common.h"

PlacedSquares::PlacedSquares()
{
    removeAllPlacedSquares();
}

void PlacedSquares::removeAllPlacedSquares()
{
    Drawer::eraseAllPlacedSquares(*this);

    for(int x = GameArenaParameters::minBlockColumns; x <= GameArenaParameters::maxBlockColumns; x++)
    {
        for(int y = GameArenaParameters::minBlockRows; y <= GameArenaParameters::maxBlockRows; y++)
        {
            coordinatesToSquaresMapping_.insert(Coordinates(x, y), nullptr);
        }
    }
}

void PlacedSquares::addSquare(const Coordinates& coordinates, QColor color, PlacedSquares& placedSquares)
{
    if(coordinatesToSquaresMapping_.value(coordinates) == nullptr)
    {
        Drawer::drawSquare(coordinates, color, placedSquares);
    }
    else
    {
        throw std::runtime_error("Placing square on non-empty field");
    }
}

void PlacedSquares::removeSquare(const Coordinates& coordinates)
{
    if(coordinatesToSquaresMapping_.value(coordinates) != nullptr)
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
        removeSquare(Coordinates(x, y));
    }
}

QVector<int> PlacedSquares::findFullRows() const
{
    QVector<int> fullRows;

    /*Go through all rows*/
    for(int row = 1; row <= GameArenaParameters::maxBlockRows; row++)
    {
        for(int column = 1; column <= GameArenaParameters::maxBlockColumns; column++)
        {
            Coordinates coordinates(column, row);

            if(coordinatesToSquaresMapping_.value(coordinates) == nullptr)
            {
                break;
            }

            if(column == GameArenaParameters::maxBlockColumns)
            {
                fullRows.append(row);
            }
        }
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
        for(int y = removedRow - 1; y > GameArenaParameters::minBlockRows; y--)
        {
            Coordinates coordinates(x, y);
            Coordinates coordinatesOneRowBelow(x, y + 1);

            coordinatesToSquaresMapping_[coordinatesOneRowBelow] = coordinatesToSquaresMapping_[coordinates];
            coordinatesToSquaresMapping_[coordinates] = nullptr;
        }
    }
}
