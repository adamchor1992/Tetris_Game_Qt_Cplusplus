#include "block.h"
#include "config.h"

Block::Block(const BlockShape& blockShape, const QColor& color) :
        blockShape_(blockShape),
        color_(color),
        rotationStateToRotationCoefficientsContainerMapping(blockShapeToRotationStateToRotationCoefficientsContainerMapping.at(blockShape)),
        rotationStateIterator_(rotationStateToRotationCoefficientsContainerMapping.size())
{
    squaresCoordinates_ = BlockCoordinatesArray{Config::Block::STARTING_CENTRAL_SQUARE_COORDINATES,
                                                Config::Block::STARTING_CENTRAL_SQUARE_COORDINATES + rotationStateToRotationCoefficientsContainerMapping.at(rotationStateIterator_.current()).getRotationCoefficientsPair(0),
                                                Config::Block::STARTING_CENTRAL_SQUARE_COORDINATES + rotationStateToRotationCoefficientsContainerMapping.at(rotationStateIterator_.current()).getRotationCoefficientsPair(1),
                                                Config::Block::STARTING_CENTRAL_SQUARE_COORDINATES + rotationStateToRotationCoefficientsContainerMapping.at(rotationStateIterator_.current()).getRotationCoefficientsPair(2)};
}

[[nodiscard]] const BlockCoordinatesArray& Block::getAllSquaresCoordinates() const
{
    return squaresCoordinates_;
}

[[nodiscard]] BlockCoordinatesArray& Block::getAllSquaresCoordinates()
{
    return squaresCoordinates_;
}

[[nodiscard]] const Coordinates& Block::getSquareCoordinates(int i) const
{
    return squaresCoordinates_.at(i);
}

[[nodiscard]] Coordinates& Block::getSquareCoordinates(int i)
{
    return squaresCoordinates_.at(i);
}

Coordinates Block::getCentralSquareCoordinates() const
{
    return getSquareCoordinates(0);
}

std::ostream& operator<<(std::ostream& os, Block& block)
{
    for(const auto& coordinates : block.getAllSquaresCoordinates())
    {
        os << coordinates;
    }

    return os;
}

void Block::setBlockCoordinates(const BlockCoordinatesArray& blockCoordinatesArray)
{
    squaresCoordinates_ = blockCoordinatesArray;
}
