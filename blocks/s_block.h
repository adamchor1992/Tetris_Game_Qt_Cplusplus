#pragma once

#include "block_base.h"

class SBlock : public BlockBase
{
public:
    explicit SBlock();
    void rotateBlock(const PlacedSquares& placedSquares) override;

private:
    static inline const QVector<int> transformationCoefficientsVsCentralSquare_ {-1, +1, 0, +1, +1, 0};
};
