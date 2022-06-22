#pragma once

#include "block_base.h"

class OBlock : public BlockBase
{
public:
    explicit OBlock();
    void rotate(const PlacedSquares&) override;

private:
    inline static const TransformationCoefficients transformationCoefficientsVsCentralSquare_ {0, +1, +1, +1, +1, 0};
};
