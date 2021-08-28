#pragma once

#include "block_base.h"

class IBlock : public BlockBase
{
public:
    explicit IBlock();
    void RotateBlock(const PlacedBlocks& placedBlocks) override;

private:
    int m_CurrentRotation;
};
