#ifndef ZBLOCK_H
#define ZBLOCK_H
#include "block.h"

class ZBlock : public Block
{
public:
    explicit ZBlock();

    void rotateBlock();

private:
    int current_rotation;
};

#endif // ZBLOCK_H
