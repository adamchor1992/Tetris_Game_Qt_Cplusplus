#include "z_block.h"

ZBlock::ZBlock() : BlockBase(transformationCoefficientsVsCentralSquare_)
{

}

void ZBlock::rotateBlock(const PlacedSquares& placedSquares)
{
    QVector<RotationCoefficients> rotationCoefficients;

    int nextRotationState = -1;

    if(currentRotation_ == 0)
    {
        rotationCoefficients.append(QVector<RotationCoefficients>{RotationCoefficients{0, -1}, RotationCoefficients{-1, 0}, RotationCoefficients{-1, +1}});
        nextRotationState = 1;
    }
    else if(currentRotation_ == 1)
    {
        rotationCoefficients.append(QVector<RotationCoefficients>{RotationCoefficients{-1, 0}, RotationCoefficients{0, +1}, RotationCoefficients{+1, +1}});
        nextRotationState = 0;
    }

    if(processRotation(placedSquares, rotationCoefficients))
    {
        currentRotation_ = nextRotationState;
    }
}
