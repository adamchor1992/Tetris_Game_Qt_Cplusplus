#pragma once

#include "block.h"

class TBlock : public Block
{
public:
    explicit TBlock();
    void RotateBlock() override;

private:
    int m_CurrentRotation;
};
