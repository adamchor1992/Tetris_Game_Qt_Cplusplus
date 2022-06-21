#pragma once

#include "block_base.h"

class TBlock : public BlockBase
{
public:
    explicit TBlock();
    void rotate(const PlacedSquares& placedSquares) override;

private:
    inline static const std::array<TransformationCoefficients, 3> transformationCoefficientsVsCentralSquare_ {TransformationCoefficients{-1, 0}, TransformationCoefficients{0, +1}, TransformationCoefficients{+1, 0}};

    inline static const QMap<RotationState, std::array<RotationCoefficients, 3>> rotationCoefficients_{
        {0, std::array<RotationCoefficients, 3>{RotationCoefficients{0, -1}, RotationCoefficients{-1, 0}, RotationCoefficients{0, +1}}},
        {1, std::array<RotationCoefficients, 3>{RotationCoefficients{+1, 0}, RotationCoefficients{0, -1}, RotationCoefficients{-1, 0}}},
        {2, std::array<RotationCoefficients, 3>{RotationCoefficients{0, +1}, RotationCoefficients{+1, 0}, RotationCoefficients{0, -1}}},
        {3, std::array<RotationCoefficients, 3>{RotationCoefficients{-1, 0}, RotationCoefficients{0, +1}, RotationCoefficients{+1, 0}}}};
};
