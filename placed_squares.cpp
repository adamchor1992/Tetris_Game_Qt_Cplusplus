#include "placed_squares.h"
#include "drawer.h"
#include "utilities.h"

PlacedSquares::PlacedSquares()
{
    /*Initialize m_PlacedBlocksMap with all null pointers*/
    for(int column = 1; column <= GameArenaParameters::MAX_BLOCK_COLUMNS; column++)
    {
        for(int row=1; row <= GameArenaParameters::MAX_BLOCK_ROWS; row++)
        {
            m_PlacedBlocksMap.insert(Coordinates(column, row), PlacedSquares::SquarePresence::NO_SQUARE);
        }
    }

    qDebug() << "Size of m_PlacedBlocksMap: " << m_PlacedBlocksMap.size();
}

void PlacedSquares::ClearPlacedBlocks()
{
    /*Initialize m_PlacedBlocksMap with all null pointers*/
    for(int column = 1; column <= GameArenaParameters::MAX_BLOCK_COLUMNS; column++)
    {
        for(int row = 1; row <= GameArenaParameters::MAX_BLOCK_ROWS; row++)
        {
            m_PlacedBlocksMap.insert(Coordinates(column, row), PlacedSquares::SquarePresence::NO_SQUARE);
        }
    }

    Drawer::RemoveAllPlacedBlocks();
}

void PlacedSquares::AddSquare(const Coordinates& coordinates)
{
    if(m_PlacedBlocksMap.value(coordinates) == PlacedSquares::SquarePresence::NO_SQUARE)
    {
        m_PlacedBlocksMap[coordinates] = PlacedSquares::SquarePresence::SQUARE_PRESENT;
    }
    else
    {
        assert(false);
    }
}

void PlacedSquares::RemoveSquare(const Coordinates& coordinates)
{
    if(m_PlacedBlocksMap.value(coordinates) == PlacedSquares::SquarePresence::SQUARE_PRESENT)
    {
        m_PlacedBlocksMap[coordinates] = PlacedSquares::SquarePresence::NO_SQUARE;
    }
    else
    {
        assert(false);
    }
}

void PlacedSquares::RemoveRow(int rowNumber)
{
    if(rowNumber < GameArenaParameters::MIN_BLOCK_ROWS || rowNumber > GameArenaParameters::MAX_BLOCK_ROWS)
    {
        assert(false);
    }

    for(int column = 1; column <= GameArenaParameters::MAX_BLOCK_COLUMNS; column++)
    {
        RemoveSquare(Coordinates(column, rowNumber));
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

            if(m_PlacedBlocksMap.value(coordinates) == PlacedSquares::SquarePresence::NO_SQUARE)
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
    QMap<Coordinates, PlacedSquares::SquarePresence> temporaryPlacedBlocksMap;

    /*Initialize temporaryPlacedBlocksArray with null pointers representing each square block*/
    for(int column=1; column <= GameArenaParameters::MAX_BLOCK_COLUMNS; column++)
    {
        for(int row=1; row <= GameArenaParameters::MAX_BLOCK_ROWS; row++)
        {
            temporaryPlacedBlocksMap.insert(Coordinates(column,row), PlacedSquares::SquarePresence::NO_SQUARE);
        }
    }

    for(int row = GameArenaParameters::MAX_BLOCK_ROWS; row > removedRow; row--)
    {
        /*Copy unchanged square block positions below deleted row from m_PlacedBlocksMap to temporaryPlacedBlocksMap*/
        for(int column = 1; column <= GameArenaParameters::MAX_BLOCK_COLUMNS; column++)
        {
            Coordinates coordinates(column, row);

            temporaryPlacedBlocksMap.insert(coordinates, m_PlacedBlocksMap.value(coordinates));
        }
    }

    /*Drop all rows by one*/
    for(int row = removedRow; row > 1; row--)
    {
        for(int column = 1; column <= GameArenaParameters::MAX_BLOCK_COLUMNS; column++)
        {
            Coordinates coordinates(column, row);
            Coordinates coordinatesOneRowBelow(column, row-1);

            temporaryPlacedBlocksMap.insert(coordinates, m_PlacedBlocksMap.value(coordinatesOneRowBelow));
        }
    }

    m_PlacedBlocksMap = temporaryPlacedBlocksMap;
}
