#pragma once
#include "Scene.h"
#include "engine/GameEngine.h"
#include "engine/entities/EntityManager.h"
#include "engine/entities/EPlayer.h"

class ScenePlay : public Scene
{
    float elapsedTimeSinceLastEnemySpawn_ = 0.0f;
    float enemySpawnMaxTime;
    std::shared_ptr<EPlayer> player_;
public:
    ScenePlay(GameEngine* gameEngine, float enemySpawnTime);

    void update(float dt) override;
    void sRender(float dt) override;
    void sDoAction(const Action& action) override;
    
    // systems
    void sAnimation();
    void sMovement(float dt);
    void sEnemySpawner(float dt);
    void sCollision();
    void sLifespan(float dt);
    void sDebug();
    
    void spawnEnemyDeathParticles(Entity* get);
};
