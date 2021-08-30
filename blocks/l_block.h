#pragma once

#include "block_base.h"

class LBlock : public BlockBase
{
public:
    explicit LBlock();
    void RotateBlock(const PlacedSquares& placedSquares) override;

private:
    int m_CurrentRotation;
};
