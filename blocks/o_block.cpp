#include "o_block.h"

OBlock::OBlock() : BlockBase()
{
    const QVector<int> transformationCoefficientsVsCentralSquare {0, +1, +1, +1, +1, 0};

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

void OBlock::RotateBlock(const PlacedSquares&)
{
    /*This block does not rotate*/
}
