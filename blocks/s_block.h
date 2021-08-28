#pragma once

#include "block_base.h"

class SBlock : public BlockBase
{
public:
    explicit SBlock();
    void RotateBlock(const PlacedBlocks& placedBlocks) override;

private:
    int m_CurrentRotation;
};
