#pragma once

#include "abstract_block.h"

class OBlock : public AbstractBlock
{
public:
    explicit OBlock(const QColor& color);
    void rotate(const PlacedSquares&) override;

private:
    inline static const TransformationCoefficients transformationCoefficientsVsCentralSquare_ {0, +1, +1, +1, +1, 0};
};
