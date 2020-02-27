#include "placed_blocks.h"

PlacedBlocks::PlacedBlocks()
{
    for(int column=1; column<=10; column++)
    {
        for(int row=1; row<=20; row++)
        {
            m_PlacedBlocksArray.insert(QPair<int,int>(column,row),nullptr);
        }
    }

    qDebug() << "Size of placedblocksarray: " << m_PlacedBlocksArray.size();
}

void PlacedBlocks::AddSquare(int x, int y, QGraphicsRectItem* p_SquareGraphicsItem)
{
    //ATTENTION, THIS METHOD DOES NOT CHECK ANYTHING!!!
    QPair<int,int> coordinatesPair(x,y);
    m_PlacedBlocksArray[coordinatesPair] = p_SquareGraphicsItem;
}

int PlacedBlocks::FindFullRows() const
{
    //go through all elements' keys
    for(int row = 1; row <= 20; row++)
    {
        for(int column = 1; column <= 10; column++)
        {
            if(m_PlacedBlocksArray.value(QPair<int,int>(column,row)) == nullptr)
            {
                break;
            }
            if(column == 10)
            {
                return row;
            }
        }
    }

    return 0;
}

void PlacedBlocks::DropRowsAbove(int deletedRow)
{
    //drop all rows above deleted row
    QMap<QPair<int,int>,QGraphicsRectItem*> temporaryPlacedBlocksArray;

    for(int column=1; column<=10; column++)
    {
        for(int row=1; row<=20; row++)
        {
            temporaryPlacedBlocksArray.insert(QPair<int,int>(column,row), nullptr);
        }
    }

    for(int row = 20; row > deletedRow; row--)
    {
        //copy unchanged positions from placedblockarray to temporaryplacedblockarray
        for(int column = 1; column <= 10; column++)
        {
            //insert key-value pairs
            temporaryPlacedBlocksArray.insert(QPair<int,int>(column,row), m_PlacedBlocksArray.value(QPair<int,int>(column,row)));
        }
    }

    for(int row = deletedRow; row > 1; row--)
    {
        for(int column = 1; column <= 10; column++)
        {
            //drop all rows by one
            temporaryPlacedBlocksArray.insert(QPair<int,int>(column,row),m_PlacedBlocksArray.value(QPair<int,int>(column,row-1)));
        }
    }

    m_PlacedBlocksArray = temporaryPlacedBlocksArray;
}

void PlacedBlocks::DeleteSquare(int x, int y)
{
    try
    {
        if(x < 1 || x > 10)
        {
            throw 1;
        }
        if(y < 1 || y > 20)
        {
            throw 2;
        }
    }
    catch(int exception)
    {
        switch(exception)
        {
        case 1:
            qDebug() << "Wrong x coordinate";
            return;
        case 2:
            qDebug() << "Wrong y coordinate";
            return;
        default:
            qDebug() << "Unknown exception in CheckCoordinatesValidity method";
            return;
        }
    }

    QPair<int,int> coordinates(x,y);

    if(m_PlacedBlocksArray.value(coordinates) == nullptr)
    {
        qDebug() << "Element is already 0!";
        return;
    }

    m_PlacedBlocksArray[coordinates] = nullptr;
}

void PlacedBlocks::DeleteRow(int rowNumber)
{
    if(rowNumber < 1)
    {
        qDebug() << "Row number smaller than 1, error! ";
        exit(-1);
    }

    if(rowNumber > 20)
    {
        qDebug() << "Row number bigger than 20, error!";
        exit(-1);
    }

    //delete all squares belonging to row_number row
    for(int column = 1; column<=10; column++)
    {
        DeleteSquare(column, rowNumber);
    }
}
