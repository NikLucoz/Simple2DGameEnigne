#include "EnemySpawnSystem.h"
#include "../entities/EntityManager.h"

EnemySpawnSystem& EnemySpawnSystem::getInstance()
{
    static EnemySpawnSystem instance;
    return instance;
}

void EnemySpawnSystem::update(float deltaTime)
{
    if (!bIsActive_) return;
    elapsedTime -= deltaTime;
    if (elapsedTime <= 0)
    {

    }
}

void EnemySpawnSystem::spawnEnemyDeathParticle(Entity* enemy)
{
    if (enemy->hasComponent<CShape>())
    {
        auto& cShape = enemy->getComponent<CShape>();
        auto& eTransform = enemy->getComponent<CTransform>();

        float angleStep = 360.0f / cShape.point_count_;
        for (int i = 0; i < cShape.point_count_; ++i)
        {
            float angle = i * angleStep;
            angle += angleStep/2;
            float radiandAngles = sf::degrees(angle).asRadians();
            auto velX = std::cosf(radiandAngles) * 300;
            auto velY = -1 * std::sinf(radiandAngles) * 300;\

            std::shared_ptr<Entity> enemyParticle = EntityManager::getInstance().addEntity("enemy");
            enemyParticle->addComponent<CShape>(10, cShape.point_count_, cShape.fillColor_, cShape.outlineColor_, 2);
            enemyParticle->addComponent<CLifespan>(0.4);
            enemyParticle->addComponent<CTransform>(eTransform.getPosition(), Vec2f(velX, velY), eTransform.getRotation());
        }
    }
}
