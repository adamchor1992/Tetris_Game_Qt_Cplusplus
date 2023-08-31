#pragma once

#include <cstddef>

class RotationState
{
public:
    explicit RotationState(int state);

    void increment()
    { ++state_; }

    void setState(int state)
    { state_ = state; }

    [[nodiscard]] int toInt() const
    { return state_; }

    bool operator<(const RotationState& other) const
    { return state_ < other.state_; }

private:
    int state_;
};

class RotationStateIterator
{
public:
    explicit RotationStateIterator(size_t rotationStatesCount) : rotationState_(0), rotationStatesCount_(rotationStatesCount)
    {}

    void advance();

    [[nodiscard]] RotationState current() const;

    [[nodiscard]] RotationState peekNext() const;

private:
    const size_t rotationStatesCount_;
    RotationState rotationState_;
};
