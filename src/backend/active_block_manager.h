#pragma once

#include "block_factory.h"

class ActiveBlockManager
{
public:
    void createBlock();
    [[nodiscard]] bool blockExists() const;
    [[nodiscard]] const Block& getActiveBlock() const;
    [[nodiscard]] Block& getActiveBlock();

private:
    BlockFactory blockFactory_;
    std::unique_ptr<Block> activeBlock_;
};
