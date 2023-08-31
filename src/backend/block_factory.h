#pragma once

#include "model/block.h"

class BlockFactory
{
public:
    [[nodiscard]] std::unique_ptr<Block> makeBlock(const BlockShape& blockShape, const QColor& color) const;
    [[nodiscard]] std::unique_ptr<Block> makeBlock(const BlockShape& blockShape);
    std::unique_ptr<Block> makeRandomBlock();

private:
    RandomGenerator<QColor> randomColorGenerator{Config::Block::BLOCK_COLORS};
    RandomGenerator<BlockShape> randomShapeGenerator{BLOCK_SHAPES};
};
