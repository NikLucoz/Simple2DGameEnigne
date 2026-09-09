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
    ScenePlay(GameEngine* gameEngine, float enemySpawnTime) : Scene(gameEngine), enemySpawnMaxTime(enemySpawnTime)
    {
        elapsedTimeSinceLastEnemySpawn_ = enemySpawnTime;
        
        player_ = EntityManager::getInstance().addEntity<EPlayer>("player");
        Vec2f startPos = Vec2f(gameEngine_->getWindow().getSize().x / 2, gameEngine_->getWindow().getSize().y / 2);
        player_->getComponent<CTransform>().position = startPos;
        player_->startPosition = startPos;
    }

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
