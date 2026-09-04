#include "EnemySpawnSystem.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "../entities/EntityManager.h"

EnemySpawnSystem& EnemySpawnSystem::getInstance()
{
    static EnemySpawnSystem instance;
    return instance;
}

void EnemySpawnSystem::update(float deltaTime, sf::RenderWindow& window)
{
    if (!bIsActive_) return;

    elapsedTime -= deltaTime;
    if (elapsedTime <= 0.0f) {
        srand(time(0)*deltaTime);
        float randomX = static_cast<float>(rand() % window.getSize().x);
        float randomY = static_cast<float>(rand() %  window.getSize().y);
        float randomAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f * 3.14f;

        float speed = 300.0f;
        float velX = std::cos(randomAngle) * speed;
        float velY = std::sin(randomAngle) * speed;
        
        int randomPoints = 3 + rand() % (6 + 1);
        
        int r = rand() % 255;
        int g = rand() % 255;
        int b = rand() % 255;

        auto e = EntityManager::getInstance().addEntity("enemy");
        e->addComponent<CTransform>(Vec2f(randomX, randomY), Vec2f(velX, velY), 0);
        e->addComponent<CShape>(25, randomPoints, sf::Color(r, g, b), sf::Color::White, 4);
        e->addComponent<CCircleCollider>(25);

        elapsedTime = spawnMaxTime;
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
            auto velY = -1 * std::sinf(radiandAngles) * 300;

            std::shared_ptr<Entity> enemyParticle = EntityManager::getInstance().addEntity("enemy");
            enemyParticle->addComponent<CShape>(10, cShape.point_count_, cShape.fillColor_, cShape.outlineColor_, 2);
            enemyParticle->addComponent<CLifespan>(0.4);
            enemyParticle->addComponent<CTransform>(eTransform.getPosition(), Vec2f(velX, velY), eTransform.getRotation());
        }
    }
}