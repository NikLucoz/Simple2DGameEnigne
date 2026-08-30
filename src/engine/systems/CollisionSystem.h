#pragma once
#include <SFML/System/Vector2.hpp>

class EntityManager;

class CollisionSystem
{
public:
    void update(EntityManager& entity_manager, sf::Vector2u windowSize, float deltaTime);
    
};
