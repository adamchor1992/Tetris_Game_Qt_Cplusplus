#include "z_block.h"

ZBlock::ZBlock() : BlockBase(transformationCoefficientsVsCentralSquare_)
{

}

void ZBlock::rotateBlock(const PlacedSquares& placedSquares)
{
    QVector<int> rotationCoefficients;

    int nextRotationState = -1;

    if(currentRotation_ == 0)
    {
        rotationCoefficients.append(QVector<int>{0, -1, -1, 0, -1, +1});
        nextRotationState = 1;
    }
    else if(currentRotation_ == 1)
    {
        rotationCoefficients.append(QVector<int>{-1, 0, 0, +1, +1, +1});
        nextRotationState = 0;
    }

    if(processRotation(placedSquares, rotationCoefficients))
    {
        currentRotation_ = nextRotationState;
    }
}
