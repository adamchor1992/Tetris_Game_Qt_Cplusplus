#pragma once

#include "block_base.h"

class TBlock : public BlockBase
{
public:
    explicit TBlock();
    void RotateBlock(const PlacedSquares& placedSquares) override;

private:
    int m_CurrentRotation;
};
