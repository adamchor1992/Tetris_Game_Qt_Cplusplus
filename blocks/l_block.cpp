#include "l_block.h"

LBlock::LBlock() : BlockBase()
{
    const QVector<int> transformationCoefficientsVsCentralSquare {-1, +1, -1, 0, +1, 0};

    const Coordinates square1Coordinates(STARTING_CENTRAL_SQUARE_COORDINATES.GetX() + transformationCoefficientsVsCentralSquare.at(0),
                                         STARTING_CENTRAL_SQUARE_COORDINATES.GetY() + transformationCoefficientsVsCentralSquare.at(1));
    const Coordinates square2Coordinates(STARTING_CENTRAL_SQUARE_COORDINATES.GetX() + transformationCoefficientsVsCentralSquare.at(2),
                                         STARTING_CENTRAL_SQUARE_COORDINATES.GetY() + transformationCoefficientsVsCentralSquare.at(3));
    const Coordinates square3Coordinates(STARTING_CENTRAL_SQUARE_COORDINATES.GetX() + transformationCoefficientsVsCentralSquare.at(4),
                                         STARTING_CENTRAL_SQUARE_COORDINATES.GetY() + transformationCoefficientsVsCentralSquare.at(5));

    m_BlockCoordinates.append(STARTING_CENTRAL_SQUARE_COORDINATES);
    m_BlockCoordinates.append(square1Coordinates);
    m_BlockCoordinates.append(square2Coordinates);
    m_BlockCoordinates.append(square3Coordinates);

    m_CurrentRotation = 0;
}

void LBlock::RotateBlock(const PlacedSquares& placedSquares)
{
    QVector<int> rotationCoefficients;

    int nextRotationState = -1;

    if(m_CurrentRotation == 0)
    {
        rotationCoefficients.append(QVector<int>{-1, 0, 0, +1, 0, +2});
        nextRotationState = 1;
    }
    else if(m_CurrentRotation == 1)
    {
        rotationCoefficients.append(QVector<int>{0, -1, -1, 0, -2, 0});
        nextRotationState = 2;
    }
    else if(m_CurrentRotation == 2)
    {
        rotationCoefficients.append(QVector<int>{+1, 0, 0, -1, 0, -2});
        nextRotationState = 3;
    }
    else if(m_CurrentRotation == 3)
    {
        rotationCoefficients.append(QVector<int>{0, +1, +1, 0, +2, 0});
        nextRotationState = 0;
    }

    if(ProcessRotation(placedSquares, rotationCoefficients))
    {
        m_CurrentRotation = nextRotationState;
    }
}
