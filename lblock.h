#ifndef LBLOCK_H
#define LBLOCK_H
#include "block.h"

class LBlock : public Block
{
public:
    explicit LBlock();

    void rotateBlock();

private:
    int current_rotation;
};

#endif // LBLOCK_H
