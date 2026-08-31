#pragma once
#include <SFML/System/Vector2.hpp>

class EnemySpawnSystem;
class EntityManager;

class CollisionSystem
{
public:
    static CollisionSystem& getInstance();
    bool bIsActive_ = true;
    void update(sf::Vector2u windowSize, float deltaTime);
private:
    CollisionSystem() = default;
};
