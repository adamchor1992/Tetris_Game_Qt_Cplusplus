#pragma once

#include "block_base.h"

class LBlock : public BlockBase
{
public:
    explicit LBlock();
    void rotateBlock(const PlacedSquares& placedSquares) override;

private:
    inline static const QVector<TransformationCoefficients> transformationCoefficientsVsCentralSquare_ {TransformationCoefficients{-1, +1}, TransformationCoefficients{-1, 0}, TransformationCoefficients{+1, 0}};
};
