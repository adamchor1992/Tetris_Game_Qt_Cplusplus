#ifndef IBLOCK_H
#define IBLOCK_H
#include "block.h"

class IBlock : public Block
{
public:
    explicit IBlock();

    void rotateBlock();

private:
    int current_rotation;
};

#endif // IBLOCK_H
