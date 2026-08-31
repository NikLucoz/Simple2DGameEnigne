#pragma once
#include "../entities/Entity.h"

namespace sf
{
    class RenderWindow;
}

class EnemySpawnSystem
{
public:
    void update(float deltaTime, sf::RenderWindow& window);
    void spawnEnemyDeathParticle(Entity* entity);
    bool bIsActive_ = true;
    static EnemySpawnSystem& getInstance();
private:
    EnemySpawnSystem() = default;
    float elapsedTime = 1;
    float spawnMaxTime = 1;
};
