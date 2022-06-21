#pragma once

class NextRotationStateGenerator
{
public:
    explicit NextRotationStateGenerator(int statesCount) : statesCount_(statesCount)
    {}

    int operator()()
    {
        ++currentState_;

        if(currentState_ == statesCount_)
        {
            currentState_ = 0;
        }

        return currentState_;
    }

private:
    int statesCount_ {};
    int currentState_ {};
};
