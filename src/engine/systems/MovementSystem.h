#pragma once

class EPlayer;
class EntityManager;

class MovementSystem
{
    MovementSystem() = default;
public:
    bool bIsActive_ = true;
    static MovementSystem& getInstance();
    void update(EPlayer* player, float deltaTime);
};
