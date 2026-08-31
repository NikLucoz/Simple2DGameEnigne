#pragma once

class EntityManager;

class LifeSpanSystem
{
    LifeSpanSystem() = default;
public:
    bool bIsActive_ = true;
    static LifeSpanSystem& getInstance();
    void update(double delta_time);
};
