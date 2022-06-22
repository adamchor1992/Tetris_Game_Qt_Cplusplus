#include "t_block.h"

TBlock::TBlock() : BlockBase(transformationCoefficientsVsCentralSquare_, rotationCoefficients_.size())
{}

void TBlock::rotate(const PlacedSquares& placedSquares)
{
    processRotation(placedSquares, rotationCoefficients_.at(currentRotation_));
}
