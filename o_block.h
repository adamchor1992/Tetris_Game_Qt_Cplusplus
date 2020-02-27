#pragma once

#include "block.h"

class OBlock : public Block
{
public:
    explicit OBlock();
    void RotateBlock() override;

private:
    int m_CurrentRotation;
};
