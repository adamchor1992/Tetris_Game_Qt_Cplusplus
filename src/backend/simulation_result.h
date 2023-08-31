#pragma once

#include "model/block.h"

class SimulationResult
{
public:
    SimulationResult();
    explicit SimulationResult(const BlockCoordinatesArray& blockCoordinates);

    [[nodiscard]] bool isValid() const
    {return isValid_;}

    [[nodiscard]] const BlockCoordinatesArray& getBlockCoordinates() const
    { return blockCoordinates_; }

    explicit operator bool() const
    { return isValid_; }

private:
    bool isValid_{};
    BlockCoordinatesArray blockCoordinates_;
};

class BlockMovementSimulationResult : public SimulationResult
{
public:
    BlockMovementSimulationResult() = default;
    explicit BlockMovementSimulationResult(const BlockCoordinatesArray& blockCoordinates);
};

class BlockRotationSimulationResult : public SimulationResult
{
public:
    BlockRotationSimulationResult() = default;
    explicit BlockRotationSimulationResult(const BlockCoordinatesArray& blockCoordinates);
};
