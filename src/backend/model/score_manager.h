#pragma once

#include <QString>

class ScoreManager
{
public:
    void addRewardForFullRowsToScoreBalance(unsigned int fullRowsCount);
    void resetScore();
    [[nodiscard]] QString getScoreInfoText() const;

private:
    int score_{};

    void increaseScore(int score);
};
