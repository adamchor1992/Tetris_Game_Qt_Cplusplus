#include "block_factory.h"

std::unique_ptr<Block> BlockFactory::makeBlock(const BlockShape& blockShape, const QColor& color) const
{
    return std::make_unique<Block>(blockShape, color);
}

std::unique_ptr<Block> BlockFactory::makeBlock(const BlockShape& blockShape)
{
    return std::make_unique<Block>(blockShape, randomColorGenerator());
}

std::unique_ptr<Block> BlockFactory::makeRandomBlock()
{
    return makeBlock(randomShapeGenerator(), randomColorGenerator());
}
