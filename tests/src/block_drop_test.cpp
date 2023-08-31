#include "common_test_fixture.h"
#include "block_factory.h"
#include "block_movement_manager.h"

class BlockDropTest : public CommonTestFixture
{
protected:
    BlockFactory blockFactory_;
};

TEST_F(BlockDropTest, LowerBlockOneRow)
{
    auto jBlock = blockFactory_.makeBlock(BlockShape::J, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = jBlock->getAllSquaresCoordinates();

    EXPECT_EQ(jBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(1), Coordinates({4, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(2), Coordinates({6, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(3), Coordinates({6, 3}));

    BlockMovementManager::lowerBlockOneRow(*jBlock);

    EXPECT_EQ(jBlock->getSquareCoordinates(0), Coordinates({5, 3}));
    EXPECT_EQ(jBlock->getSquareCoordinates(1), Coordinates({4, 3}));
    EXPECT_EQ(jBlock->getSquareCoordinates(2), Coordinates({6, 3}));
    EXPECT_EQ(jBlock->getSquareCoordinates(3), Coordinates({6, 4}));
}

TEST_F(BlockDropTest, DropBlock)
{
    PlacedSquares placedSquares;

    auto jBlock = blockFactory_.makeBlock(BlockShape::J, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = jBlock->getAllSquaresCoordinates();

    EXPECT_EQ(jBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(1), Coordinates({4, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(2), Coordinates({6, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(3), Coordinates({6, 3}));

    BlockMovementManager::dropBlock(*jBlock, placedSquares);

    EXPECT_EQ(jBlock->getSquareCoordinates(0), Coordinates({5, 19}));
    EXPECT_EQ(jBlock->getSquareCoordinates(1), Coordinates({4, 19}));
    EXPECT_EQ(jBlock->getSquareCoordinates(2), Coordinates({6, 19}));
    EXPECT_EQ(jBlock->getSquareCoordinates(3), Coordinates({6, 20}));
}
