#include "block_base.h"
#include "drawer.h"
#include "random_number_generator.h"

#include "blocks/i_block.h"
#include "blocks/i_block.h"
#include "blocks/s_block.h"
#include "blocks/z_block.h"
#include "blocks/j_block.h"
#include "blocks/l_block.h"
#include "blocks/o_block.h"
#include "blocks/t_block.h"

BlockBase::BlockBase() : STARTING_CENTRAL_SQUARE_COORDINATES(5, 1)
{
    static RandomNumberGenerator randomNumberGenerator(0, COLORS.size() - 1);
    m_BlockColor = COLORS.at(randomNumberGenerator.GenerateRandomNumber());
}

BlockBase::~BlockBase()
{
    for(auto& pointer : m_BlockSquaresGraphicsRectItemPointers)
    {
        pointer = nullptr;
    }
}

std::unique_ptr<BlockBase> BlockBase::MakeBlock()
{
    std::unique_ptr<BlockBase> pBlock = nullptr;

    static std::map<int, QString> numberToShapeMapping = { {0,"S"}, {1, "Z"}, {2, "I"}, {3, "J"}, {4, "L"}, {5, "O"}, {6, "T"} };
    static RandomNumberGenerator randomNumberGenerator(0, numberToShapeMapping.size() - 1);

    QString shape = numberToShapeMapping.at(randomNumberGenerator.GenerateRandomNumber());

    if(shape == "S")
    {
        pBlock = std::make_unique<SBlock>();
    }
    else if(shape == "Z")
    {
        pBlock = std::make_unique<ZBlock>();
    }
    else if(shape == "I")
    {
        pBlock = std::make_unique<IBlock>();
    }
    else if(shape == "J")
    {
        pBlock = std::make_unique<JBlock>();
    }
    else if(shape == "L")
    {
        pBlock = std::make_unique<LBlock>();
    }
    else if(shape == "O")
    {
        pBlock = std::make_unique<OBlock>();
    }
    else if(shape == "T")
    {
        pBlock = std::make_unique<TBlock>();
    }
    else
    {
        qDebug() << "Unknown shape";
        assert(false);
    }

    QVector<QGraphicsRectItem*> blockSquaresGraphicsRectItemPointers = Drawer::DrawBlock(pBlock->GetBlockCoordinates(), pBlock->GetColor());

    pBlock->SetBlockSquaresGraphicsRectItemPointers(blockSquaresGraphicsRectItemPointers);

    return pBlock;
}

void BlockBase::MoveBlock(Direction direction)
{
    if(direction == Direction::left)
    {
        for(int i = 0; i < m_BlockCoordinates.size(); i++)
        {
            int currentX = m_BlockCoordinates.at(i).GetX();
            int currentY = m_BlockCoordinates.at(i).GetY();

            /*Coordinate X decreases*/
            int newX = currentX - 1;
            /*Coordinate Y does not change*/
            int newY = currentY;

            m_BlockCoordinates[i].Modify(newX, newY);

            m_BlockSquaresGraphicsRectItemPointers.at(i)->moveBy(-GameArenaParameters::BLOCK_SQUARE_SIZE, 0);
        }
    }
    else if(direction == Direction::right)
    {
        for(int i = 0; i < m_BlockCoordinates.size(); i++)
        {
            int currentX = m_BlockCoordinates.at(i).GetX();
            int currentY = m_BlockCoordinates.at(i).GetY();

            /*Coordinate X increases*/
            int newX = currentX + 1;
            /*Coordinate Y does not change*/
            int newY = currentY;

            m_BlockCoordinates[i].Modify(newX, newY);

            m_BlockSquaresGraphicsRectItemPointers.at(i)->moveBy(+GameArenaParameters::BLOCK_SQUARE_SIZE, 0);
        }
    }
}

bool BlockBase::CheckMovePossibility(Direction direction, const PlacedSquares& placedBlocks) const
{
    for(int i = 0; i < m_BlockCoordinates.size(); i++)
    {
        int currentX = m_BlockCoordinates.at(i).GetX();
        int currentY = m_BlockCoordinates.at(i).GetY();

        if(direction == Direction::left)
        {
            /*Coordinate X decreases*/
            int leftBlockX = currentX - 1;
            /*Coordinate Y does not change*/
            int leftBlockY = currentY;

            /*Check if there is left wall next to the block*/
            if(leftBlockX < GameArenaParameters::MIN_BLOCK_COLUMNS)
            {
                return false;
            }

            Coordinates leftOfBlockCoordinates(leftBlockX, leftBlockY);

            /*Check if there is any block to the left of current block*/
            if(placedBlocks.GetPlacedBlocksMap().value(leftOfBlockCoordinates) == PlacedSquares::SquarePresence::SQUARE_PRESENT)
            {
                return false;
            }
        }
        else if(direction == Direction::right)
        {
            /*Coordinate X increases*/
            int rightBlockX = currentX + 1;
            /*Coordinate Y does not change*/
            int rightBlockY = currentY;

            /*Check if there is wall next to the block*/
            if(rightBlockX > GameArenaParameters::MAX_BLOCK_COLUMNS)
            {
                return false;
            }

            Coordinates rightOfBlockCoordinates(rightBlockX, rightBlockY);

            /*Check if there is any block to the left of current block*/
            if(placedBlocks.GetPlacedBlocksMap().value(rightOfBlockCoordinates) == PlacedSquares::SquarePresence::SQUARE_PRESENT)
            {
                return false;
            }
        }
    }

    return true;
}

bool BlockBase::CheckIfRotationIsPossible(const Coordinates& centralSquareCoordinates, const QVector<int>& rotationCoefficients, const PlacedSquares& placedBlocks) const
{
    int newCentralSquareX = centralSquareCoordinates.GetX();
    int newCentralSquareY = centralSquareCoordinates.GetY();

    int newSquare1X = centralSquareCoordinates.GetX() + rotationCoefficients.at(0);
    int newSquare1Y = centralSquareCoordinates.GetY() + rotationCoefficients.at(1);

    int newSquare2X = centralSquareCoordinates.GetX() + rotationCoefficients.at(2);
    int newSquare2Y = centralSquareCoordinates.GetY() + rotationCoefficients.at(3);

    int newSquare3X = centralSquareCoordinates.GetX() + rotationCoefficients.at(4);
    int newSquare3Y = centralSquareCoordinates.GetY() + rotationCoefficients.at(5);

    if(!Coordinates::ValidateCoordinates(newCentralSquareX, newCentralSquareY) ||
            !Coordinates::ValidateCoordinates(newSquare1X, newSquare1Y)||
            !Coordinates::ValidateCoordinates(newSquare2X, newSquare2Y)||
            !Coordinates::ValidateCoordinates(newSquare3X, newSquare3Y))
    {
        qDebug() << "WRONG COORDINATES IN CheckIfRotationIsPossible";
        return false;
    }

    const QVector<Coordinates> newCoordinates {Coordinates(newCentralSquareX, newCentralSquareY), Coordinates(newSquare1X, newSquare1Y), Coordinates(newSquare2X, newSquare2Y), Coordinates(newSquare3X, newSquare3Y)};

    if(CheckForOverlappingSquares(newCoordinates, placedBlocks))
    {
        qDebug() << "OVERLAPPING SQUARES";
        return false;
    }

    return true;
}

bool BlockBase::CheckForOverlappingSquares(const QVector<Coordinates>& blockCoordinates, const PlacedSquares& placedBlocks) const
{
    for(auto& coordinates : blockCoordinates)
    {
        if(placedBlocks.GetPlacedBlocksMap().value(coordinates) == PlacedSquares::SquarePresence::SQUARE_PRESENT)
        {
            return true;
        }
    }

    return false;
}

bool BlockBase::ProcessRotation(const PlacedSquares& placedBlocks, const QVector<int>& rotationCoefficients)
{
    const Coordinates centralSquareCordinates(m_BlockCoordinates.at(0).GetX(), m_BlockCoordinates.at(0).GetY());

    if(CheckIfRotationIsPossible(centralSquareCordinates, rotationCoefficients, placedBlocks))
    {
        const int newCentralSquareX = centralSquareCordinates.GetX();
        const int newCentralSquareY = centralSquareCordinates.GetY();
        const int newSquare1X = centralSquareCordinates.GetX() + rotationCoefficients.at(0);
        const int newSquare1Y = centralSquareCordinates.GetY() + rotationCoefficients.at(1);
        const int newSquare2X = centralSquareCordinates.GetX() + rotationCoefficients.at(2);
        const int newSquare2Y = centralSquareCordinates.GetY() + rotationCoefficients.at(3);
        const int newSquare3X = centralSquareCordinates.GetX() + rotationCoefficients.at(4);
        const int newSquare3Y = centralSquareCordinates.GetY() + rotationCoefficients.at(5);

        const QPair<int, int> centralSquareDifference {newCentralSquareX - m_BlockCoordinates[0].GetX(), newCentralSquareY - m_BlockCoordinates[0].GetY()};
        const QPair<int, int> square1Difference {newSquare1X - m_BlockCoordinates[1].GetX(), newSquare1Y - m_BlockCoordinates[1].GetY()};
        const QPair<int, int> square2Difference {newSquare2X - m_BlockCoordinates[2].GetX(), newSquare2Y - m_BlockCoordinates[2].GetY()};
        const QPair<int, int> square3Difference {newSquare3X - m_BlockCoordinates[3].GetX(), newSquare3Y - m_BlockCoordinates[3].GetY()};

        m_BlockSquaresGraphicsRectItemPointers.at(0)->moveBy(centralSquareDifference.first * GameArenaParameters::BLOCK_SQUARE_SIZE,
                                                             centralSquareDifference.second * GameArenaParameters::BLOCK_SQUARE_SIZE);

        m_BlockSquaresGraphicsRectItemPointers.at(1)->moveBy(square1Difference.first * GameArenaParameters::BLOCK_SQUARE_SIZE,
                                                             square1Difference.second * GameArenaParameters::BLOCK_SQUARE_SIZE);

        m_BlockSquaresGraphicsRectItemPointers.at(2)->moveBy(square2Difference.first * GameArenaParameters::BLOCK_SQUARE_SIZE,
                                                             square2Difference.second * GameArenaParameters::BLOCK_SQUARE_SIZE);

        m_BlockSquaresGraphicsRectItemPointers.at(3)->moveBy(square3Difference.first * GameArenaParameters::BLOCK_SQUARE_SIZE,
                                                             square3Difference.second * GameArenaParameters::BLOCK_SQUARE_SIZE);

        m_BlockCoordinates[0].Modify(newCentralSquareX, newCentralSquareY);
        m_BlockCoordinates[1].Modify(newSquare1X, newSquare1Y);
        m_BlockCoordinates[2].Modify(newSquare2X, newSquare2Y);
        m_BlockCoordinates[3].Modify(newSquare3X, newSquare3Y);

        return true;
    }
    else
    {
        qDebug() << "ROTATION REJECTED";
        return false;
    }
}

bool BlockBase::IsSquareOrBottomWallUnderBlock(const PlacedSquares& placedBlocks) const
{
    for(int i = 0; i < m_BlockCoordinates.size(); i++)
    {
        int currentX = m_BlockCoordinates.at(i).GetX();
        int currentY = m_BlockCoordinates.at(i).GetY();

        /*Coordinate X does not change*/
        int belowBlockX = currentX;
        /*Coordinate Y increases*/
        int belowBlockY = currentY + 1;

        /*Check if there is bottom wall below the current block*/
        if(belowBlockY > GameArenaParameters::MAX_BLOCK_ROWS)
        {
            return true;
        }

        Coordinates belowBlockCoordinates(belowBlockX, belowBlockY);

        /*Check if there is any block below the current block*/
        if(placedBlocks.GetPlacedBlocksMap().value(belowBlockCoordinates) == PlacedSquares::SquarePresence::SQUARE_PRESENT)
        {
            return true;
        }
    }

    return false;
}

QColor BlockBase::GetColor() const
{
    return m_BlockColor;
}

void BlockBase::DropBlockOneLevel()
{
    for(int i = 0; i < m_BlockCoordinates.size(); i++)
    {
        int x = m_BlockCoordinates[i].GetX();
        int y = m_BlockCoordinates[i].GetY();

        m_BlockCoordinates[i].Modify(x, y + 1);

        m_BlockSquaresGraphicsRectItemPointers.at(i)->moveBy(0, GameArenaParameters::BLOCK_SQUARE_SIZE);
    }
}

void BlockBase::DropAndPlaceBlock(const PlacedSquares& placedBlocks)
{
    while(!IsSquareOrBottomWallUnderBlock(placedBlocks))
    {
        DropBlockOneLevel();
    }
}
