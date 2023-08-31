#include "placed_squares.h"
#include "block.h"

void PlacedSquares::addSquare(const Coordinates& squareCoordinates, const QColor& color)
{
    const auto&[_, inserted] = coordinatesToSquaresMapping_.emplace(squareCoordinates, color);

    if(!inserted)
    {
        throw std::runtime_error("Error, placing square on non-empty field");
    }
}

void PlacedSquares::removeSquare(const Coordinates& coordinates)
{
    const size_t removed = coordinatesToSquaresMapping_.erase(coordinates);

    if(removed == 0)
    {
        throw std::runtime_error("Error, trying to remove square from already empty field");
    }
}

void PlacedSquares::removeRow(int rowNumber)
{
    if(rowNumber >= Config::Arena::MINIMUM_Y && rowNumber <= Config::Arena::MAXIMUM_Y)
    {
        for(int x = Config::Arena::MINIMUM_X; x <= Config::Arena::MAXIMUM_X; ++x)
        {
            removeSquare(Coordinates{x, rowNumber});
        }
    }
    else
    {
        throw std::runtime_error("Error, wrong row number given during row removal");
    }
}

std::vector<int> PlacedSquares::findFullRowsNumbers() const
{
    std::vector<int> fullRowsNumbers;

    /*Go through all rows*/
    for(int row = Config::Arena::MINIMUM_Y; row <= Config::Arena::MAXIMUM_Y; ++row)
    {
        for(int column = Config::Arena::MINIMUM_X; column <= Config::Arena::MAXIMUM_X; ++column)
        {
            if(!isFieldOccupied(Coordinates{column, row}))
            {
                break;
            }

            if(column == Config::Arena::MAXIMUM_X)
            {
                fullRowsNumbers.push_back(row);
            }
        }
    }

    if(fullRowsNumbers.size() > 4)
    {
        throw std::runtime_error("Error, wrong full rows count: " + std::to_string(fullRowsNumbers.size()));
    }

    return fullRowsNumbers;
}

void PlacedSquares::dropRowsAboveGivenRow(int removedRow)
{
    /*Go through all columns*/
    for(int x = Config::Arena::MINIMUM_X; x <= Config::Arena::MAXIMUM_X; ++x)
    {
        /*Go through rows above given row*/
        for(int y = removedRow - 1; y > Config::Arena::MINIMUM_Y; --y)
        {
            const Coordinates coordinates{x, y};

            if(isFieldOccupied(coordinates))
            {
                const Coordinates coordinatesOneRowBelow{x, y + 1};

                if(!isFieldOccupied(coordinatesOneRowBelow))
                {
                    auto nodeHandle = coordinatesToSquaresMapping_.extract(coordinates);
                    nodeHandle.key() = coordinatesOneRowBelow;
                    coordinatesToSquaresMapping_.insert(std::move(nodeHandle));
                }
                else
                {
                    throw std::runtime_error("Error, cannot drop rows above given row. Square one row below is not empty.");
                }
            }
        }
    }
}

void PlacedSquares::placeBlock(Block& block)
{
    for(const auto& squareCoordinates : block.getAllSquaresCoordinates())
    {
        addSquare(squareCoordinates, block.getColor());
    }
}

bool PlacedSquares::isFieldOccupied(const Coordinates& coordinates) const
{
    return coordinatesToSquaresMapping_.contains(coordinates);
}
