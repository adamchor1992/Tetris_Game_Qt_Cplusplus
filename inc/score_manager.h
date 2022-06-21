#pragma once

#include <QLabel>

class ScoreManager
{
public:
    ScoreManager();
    static void connectScoreLabel(QLabel* scoreLabel);
    void rewardPlayerForFullRows(qsizetype fullRowsCount);

private:
    void increaseScore(int score) {score_ += score;}
    void updateScoreLabel() const;

    inline static QLabel* scoreLabel_;
    int score_;
};
