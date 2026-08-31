#include "MovementSystem.h"

#include <iostream>
#include <SFML/Graphics/Transform.hpp>
#include "engine/entities/EntityManager.h"
#include "../entities/EPlayer.h"

MovementSystem& MovementSystem::getInstance()
{
    static MovementSystem instance;
    return instance;
}

void MovementSystem::update(EPlayer* player, float deltaTime)
{
    if (!bIsActive_) return;

    if (player != nullptr)
    {
        auto& input = player->getComponent<CInput>();
        if (input.hasMovementInput())
        {
            auto& transform = player->getComponent<CTransform>();
            Vector2<int> movementDirection = input.getMovementDirection();
            transform.position.x += transform.velocity.x * movementDirection.x * deltaTime;
            transform.position.y += transform.velocity.y * movementDirection.y * deltaTime;
        }
    }
    
    auto& enemies = EntityManager::getInstance().getEntities("enemy");
    for (auto& e : enemies)
    {
        auto& transform = e->getComponent<CTransform>();
        transform.position.y += transform.velocity.y * deltaTime;
        transform.position.x += transform.velocity.x * deltaTime;
    }
}
