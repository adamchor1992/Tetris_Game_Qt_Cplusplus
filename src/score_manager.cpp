#include "score_manager.h"

#include <QDebug>

QLabel* ScoreManager::scoreLabel_ = nullptr;

ScoreManager::ScoreManager()
{
    score_ = 0;
    updateScoreLabel();
}

void ScoreManager::connectScoreLabel(QLabel* scoreLabel)
{
    scoreLabel_ = scoreLabel;
}

void ScoreManager::rewardPlayerForFullRows(int fullRowsCount)
{
    switch(fullRowsCount)
    {
    case 1:
        qDebug() << "1 FULL ROW, + 1 point";
        increaseScore(1);
        break;
    case 2:
        qDebug() << "2 FULL ROWS, + 3 points";
        increaseScore(3);
        break;
    case 3:
        qDebug() << "3 FULL ROWS, + 7 points";
        increaseScore(7);
        break;
    case 4:
        qDebug() << "4 FULL ROWS, + 10 points";
        increaseScore(10);
        break;
    default:
        qDebug() << "WRONG FULL ROWS NUMBER";
    }

    updateScoreLabel();
}

void ScoreManager::restartScore()
{
    score_ = 0;
    updateScoreLabel();
}

void ScoreManager::updateScoreLabel()
{
    scoreLabel_->setText("SCORE: " + QString::number(score_));
}
