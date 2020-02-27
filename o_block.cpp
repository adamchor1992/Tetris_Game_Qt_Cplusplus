#include "o_block.h"

OBlock::OBlock() : Block(QString("O"))
{
    m_CurrentRotation = 0;
}

void OBlock::RotateBlock()
{
    //this block does not rotate
}
