#pragma once

#include "block_base.h"

class JBlock : public BlockBase
{
public:
    explicit JBlock();
    void rotateBlock(const PlacedSquares& placedSquares) override;

private:
    static inline const QVector<int> transformationCoefficientsVsCentralSquare_ {-1, 0, +1, 0, +1, +1};
};
