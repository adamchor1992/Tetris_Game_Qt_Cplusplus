#include "score_manager.h"
#include <QDebug>

ScoreManager::ScoreManager()
{
    m_Score = 0;
}

void ScoreManager::ConnectScoreLabel(QLabel* scoreLabel)
{
    m_ScoreLabel = scoreLabel;
}

void ScoreManager::RewardPlayerForFullRows(int fullRowsCount)
{
    switch(fullRowsCount)
    {
    case 0:
        qDebug() << "NO FULL ROWS";
        break;
    case 1:
        qDebug() << "1 FULL ROW, + 1 point";
        IncreaseScore(1);
        break;
    case 2:
        qDebug() << "2 FULL ROWS, + 3 points";
        IncreaseScore(3);
        break;
    case 3:
        qDebug() << "3 FULL ROWS, + 7 points";
        IncreaseScore(7);
        break;
    case 4:
        qDebug() << "4 FULL ROWS, + 10 points";
        IncreaseScore(10);
        break;
    default:
        qDebug() << "WRONG FULL ROWS NUMBER";
    }

    UpdateScoreLabel();
}

void ScoreManager::RestartScore()
{
    m_Score = 0;
    UpdateScoreLabel();
}

void ScoreManager::UpdateScoreLabel()
{
    m_ScoreLabel->setText("SCORE: " + QString::number(m_Score));
}
