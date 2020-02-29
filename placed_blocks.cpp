#include "placed_blocks.h"

PlacedBlocks::PlacedBlocks()
{
    /*Initialize m_PlacedBlocksMap with all null pointers*/
    for(int column=1; column <= COLUMN_COUNT; column++)
    {
        for(int row=1; row <= ROW_COUNT; row++)
        {
            m_PlacedBlocksMap.insert(QPair<int,int>(column, row), nullptr);
        }
    }

    qDebug() << "Size of m_PlacedBlocksMap: " << m_PlacedBlocksMap.size();
}

void PlacedBlocks::AddSquare(int x, int y, QGraphicsRectItem* p_SquareGraphicsItem)
{
    if(ValidateCoordinates(x, y))
    {
        QPair<int,int> coordinatesPair(x,y);

        if(m_PlacedBlocksMap.value(coordinatesPair) == nullptr)
        {
            m_PlacedBlocksMap[coordinatesPair] = p_SquareGraphicsItem;
        }
        else
        {
            assert(false);
        }
    }
}

void PlacedBlocks::DeleteSquare(int x, int y)
{
    if(ValidateCoordinates(x, y))
    {
        QPair<int,int> coordinatesPair(x,y);

        if(m_PlacedBlocksMap.value(coordinatesPair) != nullptr)
        {
            m_PlacedBlocksMap[coordinatesPair] = nullptr;
        }
        else
        {
            assert(false);
        }
    }
}

void PlacedBlocks::DeleteRow(int rowNumber)
{
    if(rowNumber < 1 || rowNumber > ROW_COUNT)
    {
        assert(false);
    }

    for(int column = 1; column <= COLUMN_COUNT; column++)
    {
        DeleteSquare(column, rowNumber);
    }
}

int PlacedBlocks::FindFullRow() const
{
    /*Go through all rows*/
    for(int row = 1; row <= ROW_COUNT; row++)
    {
        for(int column = 1; column <= COLUMN_COUNT; column++)
        {
            QPair<int,int> coordinatesPair(column, row);

            if(m_PlacedBlocksMap.value(coordinatesPair) == nullptr)
            {
                break;
            }

            if(column == COLUMN_COUNT)
            {
                return row;
            }
        }
    }

    return 0;
}

/*Drop all rows above deleted row*/
void PlacedBlocks::DropRowsAbove(int deletedRow)
{
    QMap<QPair<int,int>,QGraphicsRectItem*> temporaryPlacedBlocksMap;

    /*Initialize temporaryPlacedBlocksArray with null pointers representing each square block*/
    for(int column=1; column <= COLUMN_COUNT; column++)
    {
        for(int row=1; row <= ROW_COUNT; row++)
        {
            temporaryPlacedBlocksMap.insert(QPair<int,int>(column,row), nullptr);
        }
    }

    for(int row = ROW_COUNT; row > deletedRow; row--)
    {
        /*Copy unchanged square block positions below deleted row from m_PlacedBlocksMap to temporaryPlacedBlocksMap*/
        for(int column = 1; column <= COLUMN_COUNT; column++)
        {
            QPair<int,int> coordinatesPair(column, row);

            temporaryPlacedBlocksMap.insert(coordinatesPair, m_PlacedBlocksMap.value(coordinatesPair));
        }
    }

    /*Drop all rows by one*/
    for(int row = deletedRow; row > 1; row--)
    {
        for(int column = 1; column <= COLUMN_COUNT; column++)
        {
            QPair<int,int> coordinatesPair(column, row);
            QPair<int,int> coordinatesPairOneRowBelow(column, row-1);

            temporaryPlacedBlocksMap.insert(coordinatesPair, m_PlacedBlocksMap.value(coordinatesPairOneRowBelow));
        }
    }

    m_PlacedBlocksMap = temporaryPlacedBlocksMap;
}

bool PlacedBlocks::ValidateCoordinates(int x, int y)
{
    if(x < 1 || x > COLUMN_COUNT)
    {
        qDebug("Wrong X coordinate");

        assert(false);
    }

    if(y < 1 || y > ROW_COUNT)
    {
        qDebug("Wrong Y coordinate");

        assert(false);
    }

    return true;
}
