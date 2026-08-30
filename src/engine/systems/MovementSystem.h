#pragma once
#include "../../../game/src/entities/EPlayer.h"
#include "../entities/EntityManager.h"

class MovementSystem
{
public:
    void update(EPlayer* player, EntityManager& entity_manager, float deltaTime);
};
