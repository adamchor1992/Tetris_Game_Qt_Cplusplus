#pragma once

#include "rotation_state.h"
#include "rotation_coefficients.h"

using RotationStateToRotationCoefficientsContainerMapping = std::map<RotationState, RotationCoefficientsContainer>;

namespace IBlock
{
    const RotationStateToRotationCoefficientsContainerMapping rotationStateToRotationCoefficientsContainerMapping_{{RotationState(0), RotationCoefficientsContainer({{-1, 0},
                                                                                                                                                                     {+1, 0},
                                                                                                                                                                     {+2, 0}})},

                                                                                                                   {RotationState(1), RotationCoefficientsContainer({{0, -1},
                                                                                                                                                                     {0, +1},
                                                                                                                                                                     {0, +2}})}};
}

namespace JBlock
{
    const RotationStateToRotationCoefficientsContainerMapping rotationStateToRotationCoefficientsContainerMapping_{{RotationState(0), RotationCoefficientsContainer({{-1, 0},
                                                                                                                                                                     {+1, 0},
                                                                                                                                                                     {+1, +1}})},

                                                                                                                   {RotationState(1), RotationCoefficientsContainer({{0,  -1},
                                                                                                                                                                     {0,  +1},
                                                                                                                                                                     {-1, +1}})},

                                                                                                                   {RotationState(2), RotationCoefficientsContainer({{+1, 0},
                                                                                                                                                                     {-1, 0},
                                                                                                                                                                     {-1, -1}})},

                                                                                                                   {RotationState(3), RotationCoefficientsContainer({{0,  +1},
                                                                                                                                                                     {0,  -1},
                                                                                                                                                                     {+1, -1}})}};
}

namespace LBlock
{
    const RotationStateToRotationCoefficientsContainerMapping rotationStateToRotationCoefficientsContainerMapping_{{RotationState(0), RotationCoefficientsContainer({{+1, 0},
                                                                                                                                                                     {-1, 0},
                                                                                                                                                                     {-1, +1}})},

                                                                                                                   {RotationState(1), RotationCoefficientsContainer({{0,  +1},
                                                                                                                                                                     {0,  -1},
                                                                                                                                                                     {-1, -1}})},

                                                                                                                   {RotationState(2), RotationCoefficientsContainer({{-1, 0},
                                                                                                                                                                     {+1, 0},
                                                                                                                                                                     {+1, -1}})},

                                                                                                                   {RotationState(3), RotationCoefficientsContainer({{0,  -1},
                                                                                                                                                                     {0,  +1},
                                                                                                                                                                     {+1, +1}})}};
}

namespace OBlock
{
    const RotationStateToRotationCoefficientsContainerMapping rotationStateToRotationCoefficientsContainerMapping_{{RotationState(0), RotationCoefficientsContainer({{+1, 0},
                                                                                                                                                                     {0,  -1},
                                                                                                                                                                     {+1, -1}})}};
}

namespace SBlock
{
    const RotationStateToRotationCoefficientsContainerMapping rotationStateToRotationCoefficientsContainerMapping_{{RotationState(0), RotationCoefficientsContainer({{-1, +1},
                                                                                                                                                                     {0,  +1},
                                                                                                                                                                     {+1, 0}})},

                                                                                                                   {RotationState(1), RotationCoefficientsContainer({{0,  -1},
                                                                                                                                                                     {+1, 0},
                                                                                                                                                                     {+1, +1}})}};
}

namespace TBlock
{
    const RotationStateToRotationCoefficientsContainerMapping rotationStateToRotationCoefficientsContainerMapping_{{RotationState(0), RotationCoefficientsContainer({{-1, 0},
                                                                                                                                                                     {0,  +1},
                                                                                                                                                                     {+1, 0}})},

                                                                                                                   {RotationState(1), RotationCoefficientsContainer({{0,  -1},
                                                                                                                                                                     {-1, 0},
                                                                                                                                                                     {0,  +1}})},

                                                                                                                   {RotationState(2), RotationCoefficientsContainer({{+1, 0},
                                                                                                                                                                     {0,  -1},
                                                                                                                                                                     {-1, 0}})},

                                                                                                                   {RotationState(3), RotationCoefficientsContainer({{0,  +1},
                                                                                                                                                                     {+1, 0},
                                                                                                                                                                     {0,  -1}})}};
}

namespace ZBlock
{
    const RotationStateToRotationCoefficientsContainerMapping rotationStateToRotationCoefficientsContainerMapping_{{RotationState(0), RotationCoefficientsContainer({{-1, 0},
                                                                                                                                                                     {0,  +1},
                                                                                                                                                                     {+1, +1}})},

                                                                                                                   {RotationState(1), RotationCoefficientsContainer({{0,  -1},
                                                                                                                                                                     {-1, 0},
                                                                                                                                                                     {-1, +1}})}};
}

const std::map<BlockShape, RotationStateToRotationCoefficientsContainerMapping> blockShapeToRotationStateToRotationCoefficientsContainerMapping{{BlockShape::I, IBlock::rotationStateToRotationCoefficientsContainerMapping_},
                                                                                                                                                {BlockShape::J, JBlock::rotationStateToRotationCoefficientsContainerMapping_},
                                                                                                                                                {BlockShape::L, LBlock::rotationStateToRotationCoefficientsContainerMapping_},
                                                                                                                                                {BlockShape::O, OBlock::rotationStateToRotationCoefficientsContainerMapping_},
                                                                                                                                                {BlockShape::S, SBlock::rotationStateToRotationCoefficientsContainerMapping_},
                                                                                                                                                {BlockShape::T, TBlock::rotationStateToRotationCoefficientsContainerMapping_},
                                                                                                                                                {BlockShape::Z, ZBlock::rotationStateToRotationCoefficientsContainerMapping_}};
