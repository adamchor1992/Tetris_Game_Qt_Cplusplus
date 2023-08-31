#pragma once

using BlockCoordinatesArray = std::array<Coordinates, 4>;

enum class Direction
{
    LEFT, RIGHT
};

enum class BlockShape
{
    S, Z, I, J, L, O, T
};

const std::vector<BlockShape> BLOCK_SHAPES{BlockShape::I, BlockShape::J, BlockShape::L, BlockShape::O, BlockShape::S, BlockShape::T, BlockShape::Z,};
