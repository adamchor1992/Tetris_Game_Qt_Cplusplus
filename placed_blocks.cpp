#include "placed_blocks.h"
#include "drawer.h"
#include "utilities.h"

PlacedBlocks::PlacedBlocks()
{
    /*Initialize m_PlacedBlocksMap with all null pointers*/
    for(int column=1; column <= GameArenaParameters::MAX_BLOCK_COLUMNS; column++)
    {
        for(int row=1; row <= GameArenaParameters::MAX_BLOCK_ROWS; row++)
        {
            m_PlacedBlocksMap.insert(QPair<int,int>(column, row), PlacedBlocks::SquarePresence::NO_SQUARE);
        }
    }

    qDebug() << "Size of m_PlacedBlocksMap: " << m_PlacedBlocksMap.size();
}

void PlacedBlocks::ClearPlacedBlocks()
{
    /*Initialize m_PlacedBlocksMap with all null pointers*/
    for(int column=1; column <= GameArenaParameters::MAX_BLOCK_COLUMNS; column++)
    {
        for(int row=1; row <= GameArenaParameters::MAX_BLOCK_ROWS; row++)
        {
            m_PlacedBlocksMap.insert(QPair<int,int>(column, row), PlacedBlocks::SquarePresence::NO_SQUARE);
        }
    }
}

void PlacedBlocks::AddSquare(int x, int y)
{
    if(utilities::ValidateCoordinates(x, y))
    {
        QPair<int,int> coordinatesPair(x, y);

        if(m_PlacedBlocksMap.value(coordinatesPair) == PlacedBlocks::SquarePresence::NO_SQUARE)
        {
            m_PlacedBlocksMap[coordinatesPair] = PlacedBlocks::SquarePresence::SQUARE_PRESENT;
        }
        else
        {
            assert(false);
        }
    }
}

void PlacedBlocks::RemoveSquare(int x, int y)
{
    if(utilities::ValidateCoordinates(x, y))
    {
        QPair<int,int> coordinatesPair(x,y);

        if(m_PlacedBlocksMap.value(coordinatesPair) == PlacedBlocks::SquarePresence::SQUARE_PRESENT)
        {
            m_PlacedBlocksMap[coordinatesPair] = PlacedBlocks::SquarePresence::NO_SQUARE;
        }
        else
        {
            assert(false);
        }
    }
}

void PlacedBlocks::RemoveRow(int rowNumber)
{
    if(rowNumber < 1 || rowNumber > GameArenaParameters::MAX_BLOCK_ROWS)
    {
        assert(false);
    }

    for(int column = 1; column <= GameArenaParameters::MAX_BLOCK_COLUMNS; column++)
    {
        RemoveSquare(column, rowNumber);
    }
}

QVector<int> PlacedBlocks::FindFullRows() const
{
    QVector<int> fullRows;

    /*Go through all rows*/
    for(int row = 1; row <= GameArenaParameters::MAX_BLOCK_ROWS; row++)
    {
        for(int column = 1; column <= GameArenaParameters::MAX_BLOCK_COLUMNS; column++)
        {
            QPair<int,int> coordinatesPair(column, row);

            if(m_PlacedBlocksMap.value(coordinatesPair) == PlacedBlocks::SquarePresence::NO_SQUARE)
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
void PlacedBlocks::DropRowsAbove(int removedRow)
{
    QMap<QPair<int,int>, PlacedBlocks::SquarePresence> temporaryPlacedBlocksMap;

    /*Initialize temporaryPlacedBlocksArray with null pointers representing each square block*/
    for(int column=1; column <= GameArenaParameters::MAX_BLOCK_COLUMNS; column++)
    {
        for(int row=1; row <= GameArenaParameters::MAX_BLOCK_ROWS; row++)
        {
            temporaryPlacedBlocksMap.insert(QPair<int,int>(column,row), PlacedBlocks::SquarePresence::NO_SQUARE);
        }
    }

    for(int row = GameArenaParameters::MAX_BLOCK_ROWS; row > removedRow; row--)
    {
        /*Copy unchanged square block positions below deleted row from m_PlacedBlocksMap to temporaryPlacedBlocksMap*/
        for(int column = 1; column <= GameArenaParameters::MAX_BLOCK_COLUMNS; column++)
        {
            QPair<int,int> coordinatesPair(column, row);

            temporaryPlacedBlocksMap.insert(coordinatesPair, m_PlacedBlocksMap.value(coordinatesPair));
        }
    }

    /*Drop all rows by one*/
    for(int row = removedRow; row > 1; row--)
    {
        for(int column = 1; column <= GameArenaParameters::MAX_BLOCK_COLUMNS; column++)
        {
            QPair<int,int> coordinatesPair(column, row);
            QPair<int,int> coordinatesPairOneRowBelow(column, row-1);

            temporaryPlacedBlocksMap.insert(coordinatesPair, m_PlacedBlocksMap.value(coordinatesPairOneRowBelow));
        }
    }

    m_PlacedBlocksMap = temporaryPlacedBlocksMap;
}
