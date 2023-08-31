#include "score_manager.h"

void ScoreManager::addRewardForFullRowsToScoreBalance(unsigned int fullRowsCount)
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
}

void ScoreManager::resetScore()
{
    score_ = 0;
}

void ScoreManager::increaseScore(int score)
{
    score_ += score;
}

QString ScoreManager::getScoreInfoText() const
{
    return "SCORE: " + QString::number(score_);
}
