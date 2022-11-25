#pragma once

#include "abstract_block.h"

class TBlock : public AbstractBlock
{
public:
    explicit TBlock(const QColor& color);
    void rotate(const PlacedSquares& placedSquares) override;

private:
    inline static const TransformationCoefficients transformationCoefficientsVsCentralSquare_ {-1, 0, 0, +1, +1, 0};

    inline static const std::map<RotationState, RotationCoefficients> rotationCoefficients_{
        {0, RotationCoefficients{0, -1, -1, 0, 0, +1}},
        {1, RotationCoefficients{+1, 0, 0, -1, -1, 0}},
        {2, RotationCoefficients{0, +1, +1, 0, 0, -1}},
        {3, RotationCoefficients{-1, 0, 0, +1, +1, 0}}};
};
