#pragma once

#include "block_base.h"

class OBlock : public BlockBase
{
public:
    explicit OBlock();
    void rotate(const PlacedSquares&) override;

private:
    inline static const std::array<TransformationCoefficients, 3> transformationCoefficientsVsCentralSquare_ {TransformationCoefficients{0, +1}, TransformationCoefficients{+1, +1}, TransformationCoefficients{+1, 0}};
};
