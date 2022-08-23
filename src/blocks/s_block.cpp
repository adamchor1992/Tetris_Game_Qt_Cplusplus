#include "s_block.h"

SBlock::SBlock(const QColor& color) : BlockBase(color, transformationCoefficientsVsCentralSquare_, rotationCoefficients_.size())
{}

void SBlock::rotate(const PlacedSquares& placedSquares)
{
    processRotation(placedSquares, rotationCoefficients_.at(currentRotation_));
}
