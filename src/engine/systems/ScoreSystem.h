#pragma once

class ScoreSystem
{
    ScoreSystem() = default;
    int score_ = 0;
public:
    static ScoreSystem& getInstance();
    int getScore();
    void setScore(int score);
    void addScore(int points);
};
