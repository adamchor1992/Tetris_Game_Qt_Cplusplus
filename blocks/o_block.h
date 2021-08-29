#pragma once

#include "block_base.h"

class OBlock : public BlockBase
{
public:
    explicit OBlock();
    void RotateBlock(const PlacedSquares&) override;

private:
    int m_CurrentRotation;
};
