#pragma once

#include "block.h"

class JBlock : public Block
{
public:
    explicit JBlock();
    void RotateBlock() override;

private:
    int m_CurrentRotation;
};
