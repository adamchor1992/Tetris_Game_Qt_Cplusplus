#include "z_block.h"

ZBlock::ZBlock(const QColor& color) : BlockBase(color, transformationCoefficientsVsCentralSquare_, rotationCoefficients_.size())
{}

void ZBlock::rotate(const PlacedSquares& placedSquares)
{
    processRotation(placedSquares, rotationCoefficients_.at(currentRotation_));
}
