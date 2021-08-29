#pragma once

#include <QLabel>

class ScoreManager
{
public:
    ScoreManager();
    void ConnectScoreLabel(QLabel* scoreLabel);
    void RewardPlayerForFullRows(int fullRowsCount);
    void RestartScore();

private:
    void SetScore(int score) {m_Score = score;}
    void IncreaseScore(int score) {m_Score += score;}
    void UpdateScoreLabel();

    QLabel* m_ScoreLabel;
    int m_Score;
};
