#include "j_block.h"

JBlock::JBlock() : BlockBase(transformationCoefficientsVsCentralSquare_, rotationCoefficients_.size())
{}

void JBlock::rotate(const PlacedSquares& placedSquares)
{
    processRotation(placedSquares, rotationCoefficients_.value(currentRotation_));
}
