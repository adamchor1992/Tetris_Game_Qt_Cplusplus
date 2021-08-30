#pragma once

#include "block_base.h"

class JBlock : public BlockBase
{
public:
    explicit JBlock();
    void RotateBlock(const PlacedSquares& placedSquares) override;

private:
    int m_CurrentRotation;
};
