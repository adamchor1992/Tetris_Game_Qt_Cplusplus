#include "l_block.h"

LBlock::LBlock() : BlockBase(transformationCoefficientsVsCentralSquare_, rotationCoefficients_.size())
{}

void LBlock::rotate(const PlacedSquares& placedSquares)
{
    processRotation(placedSquares, rotationCoefficients_.at(currentRotation_));
}
