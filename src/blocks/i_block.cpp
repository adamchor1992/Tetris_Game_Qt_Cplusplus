#include "i_block.h"

IBlock::IBlock(const QColor& color) : AbstractBlock(color, transformationCoefficientsVsCentralSquare_, rotationCoefficients_.size())
{}

void IBlock::rotate(const PlacedSquares& placedSquares)
{
    processRotation(placedSquares, rotationCoefficients_.at(currentRotation_));
}
