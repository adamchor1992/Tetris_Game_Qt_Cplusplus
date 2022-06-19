#include "l_block.h"

LBlock::LBlock() : BlockBase(transformationCoefficientsVsCentralSquare_)
{

}

void LBlock::rotateBlock(const PlacedSquares& placedSquares)
{
    QVector<RotationCoefficients> rotationCoefficients;

    int nextRotationState = -1;

    if(currentRotation_ == 0)
    {
        rotationCoefficients.append(QVector<RotationCoefficients>{RotationCoefficients{-1, 0}, RotationCoefficients{0, +1}, RotationCoefficients{0, +2}});
        nextRotationState = 1;
    }
    else if(currentRotation_ == 1)
    {
        rotationCoefficients.append(QVector<RotationCoefficients>{RotationCoefficients{0, -1}, RotationCoefficients{-1, 0}, RotationCoefficients{-2, 0}});
        nextRotationState = 2;
    }
    else if(currentRotation_ == 2)
    {
        rotationCoefficients.append(QVector<RotationCoefficients>{RotationCoefficients{+1, 0}, RotationCoefficients{0, -1}, RotationCoefficients{0, -2}});
        nextRotationState = 3;
    }
    else if(currentRotation_ == 3)
    {
        rotationCoefficients.append(QVector<RotationCoefficients>{RotationCoefficients{0, +1}, RotationCoefficients{+1, 0}, RotationCoefficients{+2, 0}});
        nextRotationState = 0;
    }

    if(processRotation(placedSquares, rotationCoefficients))
    {
        currentRotation_ = nextRotationState;
    }
}
