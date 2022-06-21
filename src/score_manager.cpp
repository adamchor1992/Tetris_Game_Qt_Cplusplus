#include "score_manager.h"

ScoreManager::ScoreManager()
{
    score_ = 0;
    updateScoreLabel();
}

void ScoreManager::connectScoreLabel(QLabel* scoreLabel)
{
    scoreLabel_ = scoreLabel;
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

    updateScoreLabel();
}

void ScoreManager::updateScoreLabel() const
{
    scoreLabel_->setText("SCORE: " + QString::number(score_));
}
