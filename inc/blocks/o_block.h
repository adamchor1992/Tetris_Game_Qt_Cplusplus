#pragma once

#include "block_base.h"

class OBlock : public BlockBase
{
public:
    explicit OBlock();
    void rotateBlock(const PlacedSquares&) override;

private:
    inline static const QVector<TransformationCoefficients> transformationCoefficientsVsCentralSquare_ {TransformationCoefficients{0, +1}, TransformationCoefficients{+1, +1}, TransformationCoefficients{+1, 0}};
};
