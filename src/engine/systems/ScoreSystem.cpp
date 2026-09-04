#include "ScoreSystem.h"

ScoreSystem& ScoreSystem::getInstance()
{
    static ScoreSystem instance;
    return instance;
}

int ScoreSystem::getScore()
{
    return score_;
}

void ScoreSystem::setScore(int score)
{
    score_ = score;
}

void ScoreSystem::addScore(int points)
{
    score_ += points;
}

