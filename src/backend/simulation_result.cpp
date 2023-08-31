#include "simulation_result.h"

SimulationResult::SimulationResult() : blockCoordinates_{}
{
    isValid_ = false;
}

SimulationResult::SimulationResult(const BlockCoordinatesArray& blockCoordinates) : blockCoordinates_(blockCoordinates)
{
    isValid_ = true;
}

BlockMovementSimulationResult::BlockMovementSimulationResult(const BlockCoordinatesArray& blockCoordinates) : SimulationResult(blockCoordinates)
{}

BlockRotationSimulationResult::BlockRotationSimulationResult(const BlockCoordinatesArray& blockCoordinates) : SimulationResult(blockCoordinates)
{}
