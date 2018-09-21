#ifndef JBLOCK_H
#define JBLOCK_H
#include "block.h"

class JBlock : public Block
{
public:
    explicit JBlock();

    void rotateBlock();

private:
    int current_rotation;
};

#endif // JBLOCK_H
