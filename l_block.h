#pragma once

#include "block.h"

class LBlock : public Block
{
public:
    explicit LBlock();
    void RotateBlock() override;

private:
    int m_CurrentRotation;
};
