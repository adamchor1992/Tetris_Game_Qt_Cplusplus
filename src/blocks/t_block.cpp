#include "t_block.h"

TBlock::TBlock(const QColor& color) : BlockBase(color, transformationCoefficientsVsCentralSquare_, rotationCoefficients_.size())
{}

void TBlock::rotate(const PlacedSquares& placedSquares)
{
    processRotation(placedSquares, rotationCoefficients_.at(currentRotation_));
}
