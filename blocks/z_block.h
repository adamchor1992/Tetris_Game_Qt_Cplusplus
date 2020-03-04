#pragma once

#include "block_base.h"

class ZBlock : public BlockBase
{
public:
    explicit ZBlock();
    void RotateBlock(PlacedBlocks const& placedBlocks) override;

private:
    int m_CurrentRotation;
};
