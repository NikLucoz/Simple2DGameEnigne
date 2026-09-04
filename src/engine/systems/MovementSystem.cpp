#include "MovementSystem.h"

#include <iostream>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Time.hpp>

#include "engine/entities/EntityManager.h"
#include "../entities/EPlayer.h"
#include "engine/components/CSpecialBullet.h"

MovementSystem& MovementSystem::getInstance()
{
    static MovementSystem instance;
    return instance;
}

void MovementSystem::update(EPlayer* player, float deltaTime, sf::Clock clock)
{
    if (!bIsActive_) return;

    if (player != nullptr)
    {
        auto& input = player->getComponent<CInput>();
        if (input.hasMovementInput())
        {
            auto& transform = player->getComponent<CTransform>();
            Vector2<int> movementDirection = input.getMovementDirection();
            transform.position.x += transform.velocity.x * movementDirection.x * deltaTime;
            transform.position.y += transform.velocity.y * movementDirection.y * deltaTime;
        }
    }
    
    std::vector<std::string> tags{"bullet", "enemy"};
    auto movable_entities = EntityManager::getInstance().getEntities(tags);
    for (auto& e : movable_entities)
    {
        if (!e->hasComponent<CTransform>()) continue;
        auto& transform = e->getComponent<CTransform>();
        transform.position.y += transform.velocity.y * deltaTime;
        transform.position.x += transform.velocity.x * deltaTime;
    }
    
    tags = {"specialBullet"};
    auto specialBullets = EntityManager::getInstance().getEntities(tags);
    for (auto& sb : specialBullets)
    {
        if (!sb->hasComponent<CTransform>()) continue;
        
        if (!sb->hasComponent<CSpecialBullet>())
            sb->addComponent<CSpecialBullet>();
    
        auto& bulletData = sb->getComponent<CSpecialBullet>();
        bulletData.oscillationTime += deltaTime;
        float oscillationAmplitude = 15.0f;
        
        float sinValue = std::sin(bulletData.oscillationTime * 8.0f);
        
        auto& transform = sb->getComponent<CTransform>();
        float velocityMagnitude = transform.velocity.magnitude();
    
        if (velocityMagnitude > 0.0f)
        {
            float dirX = transform.velocity.x / velocityMagnitude;
            float dirY = transform.velocity.y / velocityMagnitude;
            
            // per applicare l'oscillazione del sin devo ruotare di 90° in senso orario
            Vec2f rotatedDirection = Vec2f(dirY, -dirX);
            Vec2f oscillation = rotatedDirection * oscillationAmplitude * sinValue;
            
            transform.position.x += oscillation.x + transform.velocity.x * deltaTime;
            transform.position.y += oscillation.y + transform.velocity.y * deltaTime;
        }
    }
}
