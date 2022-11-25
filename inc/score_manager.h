#pragma once

#include <QLabel>

class ScoreManager : public QObject
{
Q_OBJECT

signals:
    void scoreUpdatedEvent(int score);

public:
    ScoreManager();
    void rewardPlayerForFullRows(qsizetype fullRowsCount);

    [[nodiscard]] int getScore() const
    { return score_; }

    void resetScore();

private:
    void increaseScore(int score)
    { score_ += score; }

    int score_;
};
