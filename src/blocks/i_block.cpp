#include "i_block.h"

IBlock::IBlock() : BlockBase(transformationCoefficientsVsCentralSquare_)
{

}

void IBlock::rotateBlock(const PlacedSquares& placedSquares)
{
    QVector<int> rotationCoefficients;

    int nextRotationState = -1;

    if(currentRotation_ == 0)
    {
        rotationCoefficients.append(QVector<int>{0, -1, 0, +1, 0, +2});
        nextRotationState = 1;
    }
    else if(currentRotation_ == 1)
    {
        rotationCoefficients.append(QVector<int>{-1, 0, +1, 0, +2, 0});
        nextRotationState = 0;
    }

    if(processRotation(placedSquares, rotationCoefficients))
    {
        currentRotation_ = nextRotationState;
    }
}
