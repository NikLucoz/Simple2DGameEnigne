#include "MovementSystem.h"

#include <iostream>
#include <SFML/Graphics/Transform.hpp>
#include "engine/entities/EntityManager.h"
#include "../../../game/src/entities/EPlayer.h"

void MovementSystem::update(EPlayer* player, EntityManager& entity_manager, float deltaTime)
{
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
    
    auto& enemies = entity_manager.getEntities("enemy");
    for (auto& e : enemies)
    {
        auto& transform = e->getComponent<CTransform>();
        // generate random dir
        transform.position.y += transform.velocity.y * deltaTime;
        transform.position.x += transform.velocity.x * deltaTime;
    }
}
