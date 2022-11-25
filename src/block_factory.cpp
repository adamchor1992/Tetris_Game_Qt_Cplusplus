#include "block_factory.h"
#include "blocks/i_block.h"
#include "blocks/s_block.h"
#include "blocks/z_block.h"
#include "blocks/j_block.h"
#include "blocks/l_block.h"
#include "blocks/o_block.h"
#include "blocks/t_block.h"

std::unique_ptr<AbstractBlock> BlockFactory::makeBlock(const BlockShape& shape, const QColor& color)
{
    std::unique_ptr<AbstractBlock> ptr;

    switch(shape)
    {
        case BlockShape::S:
            ptr = std::make_unique<SBlock>(color);
            break;
        case BlockShape::Z:
            ptr = std::make_unique<ZBlock>(color);
            break;
        case BlockShape::I:
            ptr = std::make_unique<IBlock>(color);
            break;
        case BlockShape::J:
            ptr = std::make_unique<JBlock>(color);
            break;
        case BlockShape::L:
            ptr = std::make_unique<LBlock>(color);
            break;
        case BlockShape::O:
            ptr = std::make_unique<OBlock>(color);
            break;
        case BlockShape::T:
            ptr = std::make_unique<TBlock>(color);
            break;
        default:
            throw std::runtime_error("Unsupported block shape");
    }

    return ptr;
}

std::unique_ptr<AbstractBlock> BlockFactory::makeRandomBlock()
{
    return makeBlock(randomShapeGenerator(), randomColorGenerator());
}
