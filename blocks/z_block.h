#pragma once

#include "block_base.h"

class ZBlock : public BlockBase
{
public:
    explicit ZBlock();
    void RotateBlock() override;

private:
    int m_CurrentRotation;
};
