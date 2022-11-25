#include "score_manager.h"
#include "log_manager.h"

ScoreManager::ScoreManager()
{
    score_ = 0;
    emit scoreUpdatedEvent(score_);
}

void ScoreManager::rewardPlayerForFullRows(qsizetype fullRowsCount)
{
    switch(fullRowsCount)
    {
        case 1:
            increaseScore(1);
            break;
        case 2:
            increaseScore(3);
            break;
        case 3:
            increaseScore(7);
            break;
        case 4:
            increaseScore(10);
            break;
        default:
            throw std::runtime_error("Wrong full rows count");
    }

    emit scoreUpdatedEvent(score_);
}

void ScoreManager::resetScore()
{
    score_ = 0;
    emit scoreUpdatedEvent(score_);
}
