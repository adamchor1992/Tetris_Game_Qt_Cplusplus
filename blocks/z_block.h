#pragma once

#include "block_base.h"

class ZBlock : public BlockBase
{
public:
    explicit ZBlock();
    void RotateBlock(const PlacedSquares& placedSquares) override;

private:
    int m_CurrentRotation;
};
