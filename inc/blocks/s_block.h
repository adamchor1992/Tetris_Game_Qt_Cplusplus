#pragma once

#include "block_base.h"

class SBlock : public BlockBase
{
public:
    explicit SBlock();
    void rotateBlock(const PlacedSquares& placedSquares) override;

private:
    inline static const QVector<TransformationCoefficients> transformationCoefficientsVsCentralSquare_ {TransformationCoefficients{-1, +1}, TransformationCoefficients{0, +1}, TransformationCoefficients{+1, 0}};
};
