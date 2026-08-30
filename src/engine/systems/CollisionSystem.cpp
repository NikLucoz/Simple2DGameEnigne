#include "CollisionSystem.h"

#include "../../../game/src/entities/EPlayer.h"
#include "engine/components/CCircleCollider.h"
#include "engine/entities/EntityManager.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>

class CCircleCollider;

void CollisionSystem::update(EntityManager& entity_manager, sf::Vector2u windowSize, float deltaTime)
{
    auto& enemies = entity_manager.getEntities("enemy");
    auto players = entity_manager.getEntities("player");
    
    if (players.empty()) return;  // Niente player = niente da fare
    
    EPlayer* player = static_cast<EPlayer*>(players.front().get());   
    auto& pTransform = player->getComponent<CTransform>();
    
    for (auto& enemy : enemies)
    {
        auto& transform = enemy->getComponent<CTransform>();
        auto& collider = enemy->getComponent<CCircleCollider>();
        
        float distance = transform.getPosition().distanceTo(pTransform.getPosition());
        
        
        if (distance <= collider.radius_)
        {
            enemy->destroy();
        }
        
        // Collision con confini del mondo
        if (transform.getPosition().x - collider.radius_ < 0 ||
            transform.getPosition().x + collider.radius_ > windowSize.x ||
            transform.getPosition().y - collider.radius_ < 0 ||
            transform.getPosition().y + collider.radius_ > windowSize.y)
        {
            std::cout << "Enemy hit boundary\n";
            enemy->destroy();
        }
    }    
}