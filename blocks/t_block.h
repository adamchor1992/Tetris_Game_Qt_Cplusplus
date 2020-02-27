#pragma once

#include "block_base.h"

class TBlock : public BlockBase
{
public:
    explicit TBlock();
    void RotateBlock() override;

private:
    int m_CurrentRotation;
};
