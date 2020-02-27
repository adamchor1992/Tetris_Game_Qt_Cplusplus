#pragma once

#include "block.h"

class IBlock : public Block
{
public:
    explicit IBlock();
    void RotateBlock() override;

private:
    int m_CurrentRotation;
};
