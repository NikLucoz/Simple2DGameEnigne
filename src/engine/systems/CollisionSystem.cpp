#include "CollisionSystem.h"
#include "../entities/EPlayer.h"
#include "engine/components/CCircleCollider.h"
#include "engine/entities/EntityManager.h"
#include <SFML/System/Vector2.hpp>

#include "EnemySpawnSystem.h"
#include "ScoreSystem.h"

class CCircleCollider;

CollisionSystem& CollisionSystem::getInstance()
{
    static CollisionSystem instance;
    return instance;
}

void CollisionSystem::update(sf::Vector2u windowSize, float deltaTime)
{
    if (!bIsActive_) return;
    auto& enemies = EntityManager::getInstance().getEntities("enemy");
    auto players = EntityManager::getInstance().getEntities("player");
    auto bullets = EntityManager::getInstance().getEntities("bullet");
    
    if (players.empty()) return;
    
    EPlayer* player = static_cast<EPlayer*>(players.front().get());   
    auto& pTransform = player->getComponent<CTransform>();
    auto& pCollider = player->getComponent<CCircleCollider>();
    
    for (auto& enemy : enemies)
    {
        if (!enemy->hasComponent<CCircleCollider>()) continue;
        auto& eTransform = enemy->getComponent<CTransform>();
        auto& eCollider = enemy->getComponent<CCircleCollider>();

        float distanceToPlayer = eTransform.getPosition().distanceToSquared(pTransform.getPosition());
        if (distanceToPlayer < (eCollider.radius_ + pCollider.radius_) * (eCollider.radius_ + pCollider.radius_))
        {
            EnemySpawnSystem::getInstance().spawnEnemyDeathParticle(enemy.get());
            enemy->destroy();
            ScoreSystem::getInstance().addScore(-200);
            pTransform.position = player->startPosition;
            break;
        }
        
        for (auto& bullet : bullets)
        {
            if (!bullet->hasComponent<CCircleCollider>()) continue;
            auto& bTransform = bullet->getComponent<CTransform>();
            auto& bCollider = bullet->getComponent<CCircleCollider>();
            
            float distanceToBullet = eTransform.getPosition().distanceToSquared(bTransform.getPosition());
            if (distanceToBullet < (eCollider.radius_ + bCollider.radius_) * eCollider.radius_)
            {
                EnemySpawnSystem::getInstance().spawnEnemyDeathParticle(enemy.get());
                enemy->destroy();
                bullet->destroy();
                ScoreSystem::getInstance().addScore(50);
                break;
            }
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
