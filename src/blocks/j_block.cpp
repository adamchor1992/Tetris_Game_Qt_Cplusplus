#include "j_block.h"

JBlock::JBlock(const QColor& color) : AbstractBlock(color, transformationCoefficientsVsCentralSquare_, rotationCoefficients_.size())
{}

void JBlock::rotate(const PlacedSquares& placedSquares)
{
    processRotation(placedSquares, rotationCoefficients_.at(currentRotation_));
}
