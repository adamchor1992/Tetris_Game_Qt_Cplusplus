#ifndef TBLOCK_H
#define TBLOCK_H
#include "block.h"

class TBlock : public Block
{
public:
    explicit TBlock();

    void rotateBlock();

private:
    int current_rotation;
};

#endif // TBLOCK_H
