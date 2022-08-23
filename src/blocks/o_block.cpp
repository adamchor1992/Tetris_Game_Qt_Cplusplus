#include "o_block.h"

OBlock::OBlock(const QColor& color) : BlockBase(color, transformationCoefficientsVsCentralSquare_, 0)
{}

void OBlock::rotate(const PlacedSquares&)
{
    /*This block does not rotate*/
}
