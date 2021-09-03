#pragma once

#include "block_base.h"

class LBlock : public BlockBase
{
public:
    explicit LBlock();
    void rotateBlock(const PlacedSquares& placedSquares) override;

private:
    static inline const QVector<int> transformationCoefficientsVsCentralSquare_ {-1, +1, -1, 0, +1, 0};
};
