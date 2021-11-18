#include "o_block.h"

OBlock::OBlock() : BlockBase(transformationCoefficientsVsCentralSquare_)
{

}

void OBlock::rotateBlock(const PlacedSquares&)
{
    /*This block does not rotate*/
}
