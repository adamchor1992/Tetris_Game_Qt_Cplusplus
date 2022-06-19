#pragma once

#include "block_base.h"

class TBlock : public BlockBase
{
public:
    explicit TBlock();
    void rotateBlock(const PlacedSquares& placedSquares) override;

private:
    inline static const QVector<TransformationCoefficients> transformationCoefficientsVsCentralSquare_ {TransformationCoefficients{-1, 0}, TransformationCoefficients{0, +1}, TransformationCoefficients{+1, 0}};
};
