#include "block_factory.h"
#include "blocks/i_block.h"
#include "blocks/s_block.h"
#include "blocks/z_block.h"
#include "blocks/j_block.h"
#include "blocks/l_block.h"
#include "blocks/o_block.h"
#include "blocks/t_block.h"
#include "log_manager.h"

#include "random_generator.h"

std::unique_ptr <BlockBase> BlockFactory::makeBlock(const BlockShape& shape, const QColor& color)
{
    switch(shape)
    {
        case BlockShape::S:
            return std::make_unique<SBlock>(color);
        case BlockShape::Z:
            return std::make_unique<ZBlock>(color);
        case BlockShape::I:
            return std::make_unique<IBlock>(color);
        case BlockShape::J:
            return std::make_unique<JBlock>(color);
        case BlockShape::L:
            return std::make_unique<LBlock>(color);
        case BlockShape::O:
            return std::make_unique<OBlock>(color);
        case BlockShape::T:
            return std::make_unique<TBlock>(color);
        default:
            throw std::runtime_error("Unsupported block shape");
    }
}

std::unique_ptr<BlockBase> BlockFactory::makeRandomBlock()
{
    return makeBlock(randomShapeGenerator(), randomColorGenerator());
}
