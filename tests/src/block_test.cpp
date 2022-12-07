#include "common_test_fixture.h"
#include "placed_squares.h"
#include "block_factory.h"

class BlockTest : public CommonTestFixture
{
protected:
    BlockTest() : coordinatesToSquaresMapping_(placedSquares_.getCoordinatesToSquaresMapping())
    {

    }

    PlacedSquares placedSquares_;
    CoordinatesToSquaresMapping& coordinatesToSquaresMapping_;
    BlockFactory blockFactory_;

private:
    void SetUp() override
    {

    }

    void TearDown() override
    {
        coordinatesToSquaresMapping_.clear();
    }
};

TEST_F(BlockTest, CreateIBlock)
{
    auto iBlock = blockFactory_.makeBlock(BlockShape::I, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = iBlock->getSquaresCoordinates();

    EXPECT_EQ(blockCoordinates.size(), 4);

    EXPECT_EQ(iBlock->getSquareCoordinates(0), Coordinates(5, 1));
    EXPECT_EQ(iBlock->getSquareCoordinates(1), Coordinates(4, 1));
    EXPECT_EQ(iBlock->getSquareCoordinates(2), Coordinates(6, 1));
    EXPECT_EQ(iBlock->getSquareCoordinates(3), Coordinates(7, 1));
}

TEST_F(BlockTest, CreateSBlock)
{
    auto sBlock = blockFactory_.makeBlock(BlockShape::S, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = sBlock->getSquaresCoordinates();

    EXPECT_EQ(blockCoordinates.size(), 4);

    EXPECT_EQ(sBlock->getSquareCoordinates(0), Coordinates(5, 1));
    EXPECT_EQ(sBlock->getSquareCoordinates(1), Coordinates(4, 2));
    EXPECT_EQ(sBlock->getSquareCoordinates(2), Coordinates(5, 2));
    EXPECT_EQ(sBlock->getSquareCoordinates(3), Coordinates(6, 1));
}

TEST_F(BlockTest, CreateZBlock)
{
    auto zBlock = blockFactory_.makeBlock(BlockShape::Z, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = zBlock->getSquaresCoordinates();

    EXPECT_EQ(blockCoordinates.size(), 4);

    EXPECT_EQ(zBlock->getSquareCoordinates(0), Coordinates(5, 1));
    EXPECT_EQ(zBlock->getSquareCoordinates(1), Coordinates(4, 1));
    EXPECT_EQ(zBlock->getSquareCoordinates(2), Coordinates(5, 2));
    EXPECT_EQ(zBlock->getSquareCoordinates(3), Coordinates(6, 2));
}

TEST_F(BlockTest, CreateJBlock)
{
    auto jBlock = blockFactory_.makeBlock(BlockShape::J, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = jBlock->getSquaresCoordinates();

    EXPECT_EQ(blockCoordinates.size(), 4);

    EXPECT_EQ(jBlock->getSquareCoordinates(0), Coordinates(5, 1));
    EXPECT_EQ(jBlock->getSquareCoordinates(1), Coordinates(4, 1));
    EXPECT_EQ(jBlock->getSquareCoordinates(2), Coordinates(6, 1));
    EXPECT_EQ(jBlock->getSquareCoordinates(3), Coordinates(6, 2));
}

TEST_F(BlockTest, CreateLBlock)
{
    auto lBlock = blockFactory_.makeBlock(BlockShape::L, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = lBlock->getSquaresCoordinates();

    EXPECT_EQ(blockCoordinates.size(), 4);

    EXPECT_EQ(lBlock->getSquareCoordinates(0), Coordinates(5, 1));
    EXPECT_EQ(lBlock->getSquareCoordinates(1), Coordinates(4, 2));
    EXPECT_EQ(lBlock->getSquareCoordinates(2), Coordinates(4, 1));
    EXPECT_EQ(lBlock->getSquareCoordinates(3), Coordinates(6, 1));
}

TEST_F(BlockTest, CreateOBlock)
{
    auto oBlock = blockFactory_.makeBlock(BlockShape::O, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = oBlock->getSquaresCoordinates();

    EXPECT_EQ(blockCoordinates.size(), 4);

    EXPECT_EQ(oBlock->getSquareCoordinates(0), Coordinates(5, 1));
    EXPECT_EQ(oBlock->getSquareCoordinates(1), Coordinates(5, 2));
    EXPECT_EQ(oBlock->getSquareCoordinates(2), Coordinates(6, 2));
    EXPECT_EQ(oBlock->getSquareCoordinates(3), Coordinates(6, 1));
}

TEST_F(BlockTest, CreateTBlock)
{
    auto tBlock = blockFactory_.makeBlock(BlockShape::T, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = tBlock->getSquaresCoordinates();

    EXPECT_EQ(blockCoordinates.size(), 4);

    EXPECT_EQ(tBlock->getSquareCoordinates(0), Coordinates(5, 1));
    EXPECT_EQ(tBlock->getSquareCoordinates(1), Coordinates(4, 1));
    EXPECT_EQ(tBlock->getSquareCoordinates(2), Coordinates(5, 2));
    EXPECT_EQ(tBlock->getSquareCoordinates(3), Coordinates(6, 1));
}

TEST_F(BlockTest, MoveBlock)
{
    auto oBlock = blockFactory_.makeBlock(BlockShape::O, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = oBlock->getSquaresCoordinates();

    oBlock->processMove(Direction::left, placedSquares_);

    EXPECT_EQ(oBlock->getSquareCoordinates(0), Coordinates(4, 1));
    EXPECT_EQ(oBlock->getSquareCoordinates(1), Coordinates(4, 2));
    EXPECT_EQ(oBlock->getSquareCoordinates(2), Coordinates(5, 2));
    EXPECT_EQ(oBlock->getSquareCoordinates(3), Coordinates(5, 1));

    oBlock->processMove(Direction::right, placedSquares_);

    EXPECT_EQ(oBlock->getSquareCoordinates(0), Coordinates(5, 1));
    EXPECT_EQ(oBlock->getSquareCoordinates(1), Coordinates(5, 2));
    EXPECT_EQ(oBlock->getSquareCoordinates(2), Coordinates(6, 2));
    EXPECT_EQ(oBlock->getSquareCoordinates(3), Coordinates(6, 1));
}

TEST_F(BlockTest, DropBlockOneLevel)
{
    auto sBlock = blockFactory_.makeBlock(BlockShape::S, DEFAULT_SQUARE_COLOR);

    sBlock->dropBlockOneLevel();

    EXPECT_EQ(sBlock->getSquareCoordinates(0), Coordinates(5, 2));
    EXPECT_EQ(sBlock->getSquareCoordinates(1), Coordinates(4, 3));
    EXPECT_EQ(sBlock->getSquareCoordinates(2), Coordinates(5, 3));
    EXPECT_EQ(sBlock->getSquareCoordinates(3), Coordinates(6, 2));

    sBlock->dropBlockOneLevel();

    EXPECT_EQ(sBlock->getSquareCoordinates(0), Coordinates(5, 3));
    EXPECT_EQ(sBlock->getSquareCoordinates(1), Coordinates(4, 4));
    EXPECT_EQ(sBlock->getSquareCoordinates(2), Coordinates(5, 4));
    EXPECT_EQ(sBlock->getSquareCoordinates(3), Coordinates(6, 3));
}

TEST_F(BlockTest, RotateBlock)
{
    auto sBlock = blockFactory_.makeBlock(BlockShape::S, DEFAULT_SQUARE_COLOR);

    sBlock->dropBlockOneLevel();

    EXPECT_EQ(sBlock->getSquareCoordinates(0), Coordinates(5, 2));
    EXPECT_EQ(sBlock->getSquareCoordinates(1), Coordinates(4, 3));
    EXPECT_EQ(sBlock->getSquareCoordinates(2), Coordinates(5, 3));
    EXPECT_EQ(sBlock->getSquareCoordinates(3), Coordinates(6, 2));

    sBlock->rotate(placedSquares_);

    EXPECT_EQ(sBlock->getSquareCoordinates(0), Coordinates(5, 2));
    EXPECT_EQ(sBlock->getSquareCoordinates(1), Coordinates(5, 1));
    EXPECT_EQ(sBlock->getSquareCoordinates(2), Coordinates(6, 2));
    EXPECT_EQ(sBlock->getSquareCoordinates(3), Coordinates(6, 3));

    sBlock->rotate(placedSquares_);

    EXPECT_EQ(sBlock->getSquareCoordinates(0), Coordinates(5, 2));
    EXPECT_EQ(sBlock->getSquareCoordinates(1), Coordinates(6, 2));
    EXPECT_EQ(sBlock->getSquareCoordinates(2), Coordinates(5, 3));
    EXPECT_EQ(sBlock->getSquareCoordinates(3), Coordinates(4, 3));
}
