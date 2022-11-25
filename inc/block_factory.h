#pragma once

#include "abstract_block.h"

class BlockFactory
{
public:
    std::unique_ptr<AbstractBlock> makeBlock(const BlockShape& shape, const QColor& color);
    std::unique_ptr<AbstractBlock> makeRandomBlock();

private:
    RandomGenerator<QColor> randomColorGenerator{GameParameters::Block::blockColors};
    RandomGenerator<BlockShape> randomShapeGenerator{GameParameters::Block::blockShapes};
};
