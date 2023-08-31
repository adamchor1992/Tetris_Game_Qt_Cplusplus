#include "rotation_state.h"

RotationState::RotationState(int state) : state_(state)
{}

void RotationStateIterator::advance()
{
    rotationState_.increment();

    if(rotationState_.toInt() == rotationStatesCount_)
    {
        rotationState_.setState(0);
    }
}

RotationState RotationStateIterator::current() const
{
    return rotationState_;
}

RotationState RotationStateIterator::peekNext() const
{
    RotationState rotationState(rotationState_);
    rotationState.increment();

    if(rotationState.toInt() == rotationStatesCount_)
    {
        rotationState.setState(0);
    }

    return rotationState;
}
