#pragma once
#include "Entity.h"

class EPlayer : public Entity
{
public:
    EPlayer(const std::string& tag, size_t id) : Entity(tag, id)
    {
        addComponent<CTransform>(Vec2f(300.0f, 300.0f), Vec2f(300.0f, 300.0f), 0);
        addComponent<CShape>(40, 6, sf::Color::Red, sf::Color::White, 10);
        addComponent<CInput>();
        addComponent<CCircleCollider>(50);
    }
};
