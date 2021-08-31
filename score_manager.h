#pragma once

#include <QLabel>

class ScoreManager
{
public:
    ScoreManager();
    static void ConnectScoreLabel(QLabel* scoreLabel);
    void RewardPlayerForFullRows(int fullRowsCount);
    void RestartScore();

private:
    void SetScore(int score) {m_Score = score;}
    void IncreaseScore(int score) {m_Score += score;}
    void UpdateScoreLabel();

    static QLabel* m_ScoreLabel;
    int m_Score;
};
