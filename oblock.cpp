#include "oblock.h"

OBlock::OBlock() : Block(QString("O"))
{
    current_rotation = 0;
}

void OBlock::rotateBlock()
{
    //this block does not rotate
}
