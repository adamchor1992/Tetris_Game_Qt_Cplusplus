#pragma once

#include "block.h"


class SBlock : public Block
{
public:
    explicit SBlock();
    void RotateBlock() override;

private:
    int m_CurrentRotation;
};
