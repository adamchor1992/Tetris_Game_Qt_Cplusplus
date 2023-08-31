#include "common_test_fixture.h"
#include "block_factory.h"

class BlockCreationTest : public CommonTestFixture
{
protected:
    BlockFactory blockFactory_;
};

TEST_F(BlockCreationTest, CreateIBlock)
{
    auto iBlock = blockFactory_.makeBlock(BlockShape::I, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = iBlock->getAllSquaresCoordinates();

    EXPECT_EQ(iBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(iBlock->getSquareCoordinates(1), Coordinates({4, 2}));
    EXPECT_EQ(iBlock->getSquareCoordinates(2), Coordinates({6, 2}));
    EXPECT_EQ(iBlock->getSquareCoordinates(3), Coordinates({7, 2}));
}

TEST_F(BlockCreationTest, CreateJBlock)
{
    auto jBlock = blockFactory_.makeBlock(BlockShape::J, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = jBlock->getAllSquaresCoordinates();

    EXPECT_EQ(jBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(1), Coordinates({4, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(2), Coordinates({6, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(3), Coordinates({6, 3}));
}

TEST_F(BlockCreationTest, CreateLBlock)
{
    auto lBlock = blockFactory_.makeBlock(BlockShape::L, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = lBlock->getAllSquaresCoordinates();

    EXPECT_EQ(lBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(lBlock->getSquareCoordinates(1), Coordinates({6, 2}));
    EXPECT_EQ(lBlock->getSquareCoordinates(2), Coordinates({4, 2}));
    EXPECT_EQ(lBlock->getSquareCoordinates(3), Coordinates({4, 3}));
}

TEST_F(BlockCreationTest, CreateOBlock)
{
    auto oBlock = blockFactory_.makeBlock(BlockShape::O, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = oBlock->getAllSquaresCoordinates();

    EXPECT_EQ(oBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(oBlock->getSquareCoordinates(1), Coordinates({6, 2}));
    EXPECT_EQ(oBlock->getSquareCoordinates(2), Coordinates({5, 1}));
    EXPECT_EQ(oBlock->getSquareCoordinates(3), Coordinates({6, 1}));
}

TEST_F(BlockCreationTest, CreateSBlock)
{
    auto sBlock = blockFactory_.makeBlock(BlockShape::S, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = sBlock->getAllSquaresCoordinates();

    EXPECT_EQ(sBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(sBlock->getSquareCoordinates(1), Coordinates({4, 3}));
    EXPECT_EQ(sBlock->getSquareCoordinates(2), Coordinates({5, 3}));
    EXPECT_EQ(sBlock->getSquareCoordinates(3), Coordinates({6, 2}));
}

TEST_F(BlockCreationTest, CreateTBlock)
{
    auto tBlock = blockFactory_.makeBlock(BlockShape::T, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = tBlock->getAllSquaresCoordinates();

    EXPECT_EQ(tBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(tBlock->getSquareCoordinates(1), Coordinates({4, 2}));
    EXPECT_EQ(tBlock->getSquareCoordinates(2), Coordinates({5, 3}));
    EXPECT_EQ(tBlock->getSquareCoordinates(3), Coordinates({6, 2}));
}

TEST_F(BlockCreationTest, CreateZBlock)
{
    auto zBlock = blockFactory_.makeBlock(BlockShape::Z, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = zBlock->getAllSquaresCoordinates();

    EXPECT_EQ(zBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(zBlock->getSquareCoordinates(1), Coordinates({4, 2}));
    EXPECT_EQ(zBlock->getSquareCoordinates(2), Coordinates({5, 3}));
    EXPECT_EQ(zBlock->getSquareCoordinates(3), Coordinates({6, 3}));
}
