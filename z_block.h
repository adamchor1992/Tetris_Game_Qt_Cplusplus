#pragma once

#include "block.h"

class ZBlock : public Block
{
public:
    explicit ZBlock();
    void RotateBlock() override;

private:
    int m_CurrentRotation;
};
