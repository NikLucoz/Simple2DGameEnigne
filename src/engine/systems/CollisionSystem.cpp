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
    
    if (players.empty()) return;
    
    EPlayer* player = static_cast<EPlayer*>(players.front().get());   
    auto& pTransform = player->getComponent<CTransform>();
    auto& pCollider = player->getComponent<CCircleCollider>();
    
    for (auto& enemy : enemies)
    {
        auto& eTransform = enemy->getComponent<CTransform>();
        auto& eCollider = enemy->getComponent<CCircleCollider>();
        
        float distanceToPlayer = eTransform.getPosition().distanceToSquared(pTransform.getPosition());
        if (distanceToPlayer < (eCollider.radius_ + pCollider.radius_) * (eCollider.radius_ + pCollider.radius_))
        {
            if (enemy->hasComponent<CShape>())
            {
                auto& cShape = enemy->getComponent<CShape>();
                
                float angleStep = 360.0f / cShape.point_count_;
                for (int i = 0; i < cShape.point_count_; ++i)
                {
                    float angle = i * angleStep;
                    auto velX = std::cosf(angle) * 300;
                    auto velY = -1 * std::sinf(angle) * 300;

                    std::shared_ptr<Entity> enemyParticle = entity_manager.addEntity("enemyParticle");
                    enemyParticle->addComponent<CShape>(10, cShape.point_count_, cShape.fillColor_, cShape.outlineColor_, 2);
                    enemyParticle->addComponent<CLifespan>(0.4);
                    enemyParticle->addComponent<CTransform>(eTransform.getPosition(), Vec2f(velX, velY), eTransform.getRotation());
                }
            }
            enemy->destroy();
        }
        
        // Vertical wall collision
        if (eTransform.getPosition().x - eCollider.radius_ < 0 ||
            eTransform.getPosition().x + eCollider.radius_ > windowSize.x)
        {
           eTransform.velocity = eTransform.velocity.reflectionVector({1.0f, 0.0f});
        }
        
        // Horizontal wall collision
        if (eTransform.getPosition().y - eCollider.radius_ < 0 ||
            eTransform.getPosition().y + eCollider.radius_ > windowSize.y)
        {
           eTransform.velocity = eTransform.velocity.reflectionVector({0.0f, 1.0f});
        }
    }
}