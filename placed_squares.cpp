#include "placed_squares.h"
#include "drawer.h"
#include "utilities.h"

PlacedSquares::PlacedSquares()
{
    RemoveAllPlacedSquares();

    qDebug() << "Size of m_PlacedSquaresMap: " << m_PlacedSquaresMap.size();
}

void PlacedSquares::RemoveAllPlacedSquares()
{
    Drawer::EraseAllPlacedSquares(*this);

    /*Initialize m_PlacedSquaresMap with all null pointers*/
    for(int x = GameArenaParameters::MIN_BLOCK_COLUMNS; x <= GameArenaParameters::MAX_BLOCK_COLUMNS; x++)
    {
        for(int y = GameArenaParameters::MIN_BLOCK_ROWS; y <= GameArenaParameters::MAX_BLOCK_ROWS; y++)
        {
            m_PlacedSquaresMap.insert(Coordinates(x, y), nullptr);
        }
    }
}

void PlacedSquares::AddSquare(const Coordinates& coordinates, QColor color, PlacedSquares& placedSquares)
{
    if(m_PlacedSquaresMap.value(coordinates) == nullptr)
    {
        Drawer::DrawSquare(coordinates, color, placedSquares);
    }
    else
    {
        assert(false);
    }
}

void PlacedSquares::RemoveSquare(const Coordinates& coordinates)
{
    if(m_PlacedSquaresMap.value(coordinates) != nullptr)
    {
        Drawer::EraseSquare(coordinates, *this);
    }
    else
    {
        assert(false);
    }
}

void PlacedSquares::RemoveFullRow(int rowNumber)
{
    qDebug() << "REMOVING ROW";

    const int y = rowNumber;

    if(y < GameArenaParameters::MIN_BLOCK_ROWS || y > GameArenaParameters::MAX_BLOCK_ROWS)
    {
        assert(false);
    }

    for(int x = GameArenaParameters::MIN_BLOCK_COLUMNS; x <= GameArenaParameters::MAX_BLOCK_COLUMNS; x++)
    {
        RemoveSquare(Coordinates(x, y));
    }
}

QVector<int> PlacedSquares::FindFullRows() const
{
    QVector<int> fullRows;

    /*Go through all rows*/
    for(int row = 1; row <= GameArenaParameters::MAX_BLOCK_ROWS; row++)
    {
        for(int column = 1; column <= GameArenaParameters::MAX_BLOCK_COLUMNS; column++)
        {
            Coordinates coordinates(column, row);

            if(m_PlacedSquaresMap.value(coordinates) == nullptr)
            {
                break;
            }

            if(column == GameArenaParameters::MAX_BLOCK_COLUMNS)
            {
                fullRows.append(row);
            }
        }
    }

    return fullRows;
}

/*Drop all rows above deleted row*/
void PlacedSquares::DropRowsAbove(int removedRow)
{
    Drawer::DropRow(removedRow, *this);

    /*Drop all rows by one*/
    for(int x = GameArenaParameters::MIN_BLOCK_COLUMNS; x <= GameArenaParameters::MAX_BLOCK_COLUMNS; x++)
    {
        for(int y = removedRow - 1; y > GameArenaParameters::MIN_BLOCK_ROWS; y--)
        {
            Coordinates coordinates(x, y);
            Coordinates coordinatesOneRowBelow(x, y + 1);

            m_PlacedSquaresMap[coordinatesOneRowBelow] = m_PlacedSquaresMap[coordinates];
            m_PlacedSquaresMap[coordinates] = nullptr;
        }
    }
}
