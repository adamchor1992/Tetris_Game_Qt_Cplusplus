#include "o_block.h"

OBlock::OBlock() : BlockBase(transformationCoefficientsVsCentralSquare_, 0)
{}

void OBlock::rotate(const PlacedSquares&)
{
    /*This block does not rotate*/
}
