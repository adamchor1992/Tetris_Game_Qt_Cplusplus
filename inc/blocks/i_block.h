#pragma once

#include "block_base.h"

class IBlock : public BlockBase
{
public:
    explicit IBlock();
    void rotateBlock(const PlacedSquares& placedSquares) override;

private:
    inline static const QVector<TransformationCoefficients> transformationCoefficientsVsCentralSquare_ {TransformationCoefficients{-1, 0}, TransformationCoefficients{+1, 0}, TransformationCoefficients{+2, 0}};
};
