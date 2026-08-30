#pragma once

class EPlayer;
class EntityManager;

class MovementSystem
{
public:
    void update(EPlayer* player, EntityManager& entity_manager, float deltaTime);
};
