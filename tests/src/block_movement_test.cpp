#include "common_test_fixture.h"
#include "block_factory.h"
#include "block_movement_manager.h"

class BlockMovementTest : public CommonTestFixture
{
protected:
    BlockFactory blockFactory_;
    PlacedSquares placedSquares_;
    BlockMovementSimulationResult blockMovementSimulationResult;
};

TEST_F(BlockMovementTest, MoveBlockLeft)
{
    auto jBlock = blockFactory_.makeBlock(BlockShape::J, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = jBlock->getAllSquaresCoordinates();

    EXPECT_EQ(jBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(1), Coordinates({4, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(2), Coordinates({6, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(3), Coordinates({6, 3}));

    blockMovementSimulationResult = BlockMovementManager::simulateHorizontalMove(*jBlock, Direction::LEFT, placedSquares_);
    EXPECT_TRUE(blockMovementSimulationResult.isValid());
    BlockMovementManager::processMove(*jBlock, blockMovementSimulationResult);

    EXPECT_EQ(jBlock->getSquareCoordinates(0), Coordinates({4, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(1), Coordinates({3, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(2), Coordinates({5, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(3), Coordinates({5, 3}));
}

TEST_F(BlockMovementTest, MoveBlockRight)
{
    auto jBlock = blockFactory_.makeBlock(BlockShape::J, DEFAULT_SQUARE_COLOR);
    const auto& blockCoordinates = jBlock->getAllSquaresCoordinates();

    EXPECT_EQ(jBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(1), Coordinates({4, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(2), Coordinates({6, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(3), Coordinates({6, 3}));

    blockMovementSimulationResult = BlockMovementManager::simulateHorizontalMove(*jBlock, Direction::RIGHT, placedSquares_);
    EXPECT_TRUE(blockMovementSimulationResult.isValid());
    BlockMovementManager::processMove(*jBlock, blockMovementSimulationResult);

    EXPECT_EQ(jBlock->getSquareCoordinates(0), Coordinates({6, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(1), Coordinates({5, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(2), Coordinates({7, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(3), Coordinates({7, 3}));
}
