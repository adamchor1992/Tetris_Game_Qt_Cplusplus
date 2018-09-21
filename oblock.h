#ifndef OBLOCK_H
#define OBLOCK_H
#include "block.h"

class OBlock : public Block
{
public:
    explicit OBlock();

    void rotateBlock();

private:
    int current_rotation;
};

#endif // OBLOCK_H
