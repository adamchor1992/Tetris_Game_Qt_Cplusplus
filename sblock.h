#ifndef SBLOCK_H
#define SBLOCK_H
#include "block.h"

class SBlock : public Block
{
public:
    explicit SBlock();

    void rotateBlock();

private:
    int current_rotation;
};

#endif // SBLOCK_H
