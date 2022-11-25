#pragma once

#include "abstract_block.h"

class JBlock : public AbstractBlock
{
public:
    explicit JBlock(const QColor& color);
    void rotate(const PlacedSquares& placedSquares) override;

private:
    inline static const TransformationCoefficients transformationCoefficientsVsCentralSquare_ {-1, 0, +1, 0, +1, +1};

    inline static const std::map<RotationState, RotationCoefficients> rotationCoefficients_{
        {0, RotationCoefficients{-1, 0, 0, -1, 0, -2}},
        {1, RotationCoefficients{0, -1, +1, 0, +2, 0}},
        {2, RotationCoefficients{+1, 0, 0, +1, 0, +2}},
        {3, RotationCoefficients{0, +1, -1, 0, -2, 0}}};
};
