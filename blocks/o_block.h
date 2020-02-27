#pragma once

#include "block_base.h"

class OBlock : public BlockBase
{
public:
    explicit OBlock();
    void RotateBlock() override;

private:
    int m_CurrentRotation;
};
