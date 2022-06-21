#include "i_block.h"

IBlock::IBlock() : BlockBase(transformationCoefficientsVsCentralSquare_, rotationCoefficients_.size())
{}

void IBlock::rotate(const PlacedSquares& placedSquares)
{
    processRotation(placedSquares, rotationCoefficients_.value(currentRotation_));
}
