#pragma once

#include "block_base.h"

class IBlock : public BlockBase
{
public:
    explicit IBlock();
    void RotateBlock(const PlacedBlocks& placedBlocks) override;

    QVector<int> GetRotationCoefficients() {return QVector<int> {0,0};}

private:
    int m_CurrentRotation;
};
