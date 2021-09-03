#pragma once

#include "block_base.h"

class OBlock : public BlockBase
{
public:
    explicit OBlock();
    void rotateBlock(const PlacedSquares&) override;

private:
    static inline const QVector<int> transformationCoefficientsVsCentralSquare_ {0, +1, +1, +1, +1, 0};
};
