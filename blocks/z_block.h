#pragma once

#include "block_base.h"

class ZBlock : public BlockBase
{
public:
    explicit ZBlock();
    void rotateBlock(const PlacedSquares& placedSquares) override;

private:
    static inline const QVector<int> transformationCoefficientsVsCentralSquare_ {-1, 0, 0, +1, +1, +1};
};
