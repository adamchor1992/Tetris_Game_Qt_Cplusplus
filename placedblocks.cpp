#include "placedblocks.h"

PlacedBlocks::PlacedBlocks(QObject *parent) : QObject(parent)
{
    for(int column=1; column<=10; column++)
    {
        for(int row=1; row<=20; row++)
        {
            placedBlocksArray.insert(QPair<int,int>(column,row),nullptr);
        }
    }

    qDebug() << "Rozmiar placedblocksarray: " << placedBlocksArray.size();
}

void PlacedBlocks::addSquare(int x, int y, QGraphicsRectItem* square_graphic_ptr)
{
    //ATTENTION, THIS METHOD DOES NOT CHECK ANYTHING!!!
    QPair<int,int> coordinates_pair(x,y);
    placedBlocksArray[coordinates_pair] = square_graphic_ptr;
}

int PlacedBlocks::findFullRows() const
{
    //go through all elements' keys
    for(int row = 1; row <= 20; row++)
    {
        for(int column = 1; column <= 10; column++)
        {
            if(placedBlocksArray.value(QPair<int,int>(column,row)) == 0)
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

void PlacedBlocks::dropRowsAbove(int deletedRow)
{
    //drop all rows above deleted row
    QMap<QPair<int,int>,QGraphicsRectItem*> temporaryPlacedBlocksArray;

    for(int column=1; column<=10; column++)
    {
        for(int row=1; row<=20; row++)
        {
            temporaryPlacedBlocksArray.insert(QPair<int,int>(column,row),0);
        }
    }

    for(int row = 20; row > deletedRow; row--)
    {
        //copy unchanged positions from placedblockarray to temporaryplacedblockarray
        for(int column = 1; column <= 10; column++)
        {
            //insert key-value pairs
            temporaryPlacedBlocksArray.insert(QPair<int,int>(column,row),placedBlocksArray.value(QPair<int,int>(column,row)));
        }
    }

    for(int row = deletedRow; row > 1; row--)
    {
        for(int column = 1; column <= 10; column++)
        {
            //drop all rows by one
            temporaryPlacedBlocksArray.insert(QPair<int,int>(column,row),placedBlocksArray.value(QPair<int,int>(column,row-1)));
        }
    }

    placedBlocksArray = temporaryPlacedBlocksArray;
}

void PlacedBlocks::deleteSquare(int x, int y)
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
            qDebug() << "Unknown exception in checkCoordinatesValidity method";
            return;
        }
    }

    QPair<int,int> coordinates(x,y);

    if(placedBlocksArray.value(coordinates) == 0)
    {
        qDebug() << "Element is already 0!";
        return;
    }

    placedBlocksArray[coordinates] = 0;
}

void PlacedBlocks::deleteRow(int row_number)
{
    if(row_number < 1)
    {
        qDebug() << "Row number smaller than 1, error! ";
        exit(-1);
    }

    if(row_number > 20)
    {
        qDebug() << "Row number bigger than 20, error!";
        exit(-1);
    }

    //delete all squares belonging to row_number row
    for(int column = 1; column<=10; column++)
    {
        deleteSquare(column, row_number);
    }
}
