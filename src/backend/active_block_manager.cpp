#include "active_block_manager.h"

void ActiveBlockManager::createBlock()
{
    activeBlock_ = std::move(blockFactory_.makeRandomBlock());
}

bool ActiveBlockManager::blockExists() const
{
    return activeBlock_ != nullptr;
}

const Block& ActiveBlockManager::getActiveBlock() const
{
    return *activeBlock_;
}

Block& ActiveBlockManager::getActiveBlock()
{
    return *activeBlock_;
}
