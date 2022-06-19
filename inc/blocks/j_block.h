#pragma once

#include "block_base.h"

class JBlock : public BlockBase
{
public:
    explicit JBlock();
    void rotateBlock(const PlacedSquares& placedSquares) override;

private:
    inline static const QVector<TransformationCoefficients> transformationCoefficientsVsCentralSquare_ {TransformationCoefficients{-1, 0}, TransformationCoefficients{+1, 0}, TransformationCoefficients{+1, +1}};
};
