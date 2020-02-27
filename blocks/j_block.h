#pragma once

#include "block_base.h"

class JBlock : public BlockBase
{
public:
    explicit JBlock();
    void RotateBlock() override;

private:
    int m_CurrentRotation;
};
