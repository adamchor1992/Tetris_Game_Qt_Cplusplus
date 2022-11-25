#include "placed_squares.h"
#include "view/window.h"
#include "log_manager.h"

PlacedSquares::~PlacedSquares()
{
    removeAllPlacedSquares();
}

void PlacedSquares::removeAllPlacedSquares()
{
    coordinatesToSquaresMapping_.clear();

    emit placedSquaresUpdatedEvent(this);
}

void PlacedSquares::removeSquare(const Coordinates& coordinates)
{
    if(coordinatesToSquaresMapping_.contains(coordinates))
    {
        coordinatesToSquaresMapping_.remove(coordinates);
    }
    else
    {
        throw std::runtime_error("Removing square from already empty field");
    }
}

void PlacedSquares::removeRow(int rowNumber)
{
    if(rowNumber >= GameParameters::Arena::minBlockRows && rowNumber <= GameParameters::Arena::maxBlockRows)
    {
        for(int x = GameParameters::Arena::minBlockColumns; x <= GameParameters::Arena::maxBlockColumns; ++x)
        {
            removeSquare(Coordinates{x, rowNumber});
        }

        emit placedSquaresUpdatedEvent(this);
    }
    else
    {
        throw std::runtime_error("Wrong row number");
    }
}

QVector<int> PlacedSquares::findFullRows() const
{
    QVector<int> fullRows;

    /*Go through all rows*/
    for(int row = 1; row <= GameParameters::Arena::maxBlockRows; ++row)
    {
        for(int column = 1; column <= GameParameters::Arena::maxBlockColumns; ++column)
        {
            if(!coordinatesToSquaresMapping_.contains(Coordinates{column, row}))
            {
                break;
            }

            if(column == GameParameters::Arena::maxBlockColumns)
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
void PlacedSquares::dropRowsAboveRow(int removedRow)
{
    /*For all columns*/
    for(int x = GameParameters::Arena::minBlockColumns; x <= GameParameters::Arena::maxBlockColumns; ++x)
    {
        /*For rows above given row*/
        for(int y = removedRow - 1; y > GameParameters::Arena::minBlockRows; --y)
        {
            Coordinates coordinates{x, y};

            if(coordinatesToSquaresMapping_.contains(coordinates))
            {
                Coordinates coordinatesOneRowBelow{x, y + 1};

                if(!coordinatesToSquaresMapping_.contains(coordinatesOneRowBelow))
                {
                    coordinatesToSquaresMapping_[coordinates]->move(0, +1);
                    coordinatesToSquaresMapping_[coordinatesOneRowBelow] = coordinatesToSquaresMapping_[coordinates];
                    removeSquare(coordinates);
                }
                else
                {
                    throw std::runtime_error("Drop rows above error. Square one row below is not empty.");
                }
            }
        }
    }

    emit placedSquaresUpdatedEvent(this);
}

void PlacedSquares::placeBlock(AbstractBlock* abstractBlock)
{
    const QVector<Coordinates>& blockCoordinates = abstractBlock->getSquaresCoordinates();

    for(int i = 0; i < blockCoordinates.size(); ++i)
    {
        const Coordinates& squareCoordinates = blockCoordinates.at(i);

        if(!coordinatesToSquaresMapping_.contains(squareCoordinates))
        {
            coordinatesToSquaresMapping_[squareCoordinates] = abstractBlock->getSquares().at(i);
        }
        else
        {
            throw std::runtime_error("Placing square on non-empty field");
        }
    }

    emit placedSquaresUpdatedEvent(this);
}
