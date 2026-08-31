#pragma once
#include "../entities/Entity.h"

class EnemySpawnSystem
{
public:
    void update(float deltaTime);
    void spawnEnemyDeathParticle(Entity* entity);
    bool bIsActive_ = true;
    static EnemySpawnSystem& getInstance();
private:
    EnemySpawnSystem() = default;
    float elapsedTime;
    float spawnMaxTime;
};
