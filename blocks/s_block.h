#pragma once

#include "block_base.h"

class SBlock : public BlockBase
{
public:
    explicit SBlock();
    void RotateBlock(const PlacedSquares& placedSquares) override;

private:
    int m_CurrentRotation;
};
