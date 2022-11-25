#pragma once

#include "abstract_block.h"

class IBlock : public AbstractBlock
{
public:
    explicit IBlock(const QColor& color);
    void rotate(const PlacedSquares& placedSquares) override;

private:
    inline static const TransformationCoefficients transformationCoefficientsVsCentralSquare_ {-1, 0, +1, 0, +2, 0};

    inline static const std::map<RotationState, RotationCoefficients> rotationCoefficients_{
        {0, RotationCoefficients{0, -1, 0, +1, 0, +2}},
        {1, RotationCoefficients{-1, 0, +1, 0, +2, 0}}};
};
