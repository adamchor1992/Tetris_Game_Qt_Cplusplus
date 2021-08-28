#pragma once

#include "block_base.h"

class ZBlock : public BlockBase
{
public:
    explicit ZBlock();
    void RotateBlock(const PlacedBlocks& placedBlocks) override;

private:
    int m_CurrentRotation;
};
