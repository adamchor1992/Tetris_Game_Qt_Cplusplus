#pragma once

#include "block_base.h"

class BlockFactory
{
public:
    std::unique_ptr<BlockBase> makeBlock(const BlockShape& shape, const QColor& color);
    std::unique_ptr<BlockBase> makeRandomBlock();

private:
    RandomGenerator<QColor> randomColorGenerator{GameParameters::blockColors};
    RandomGenerator<BlockShape> randomShapeGenerator{GameParameters::blockShapes};
};
