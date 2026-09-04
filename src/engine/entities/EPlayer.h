#pragma once
#include "Entity.h"

class EPlayer : public Entity
{
public:
    Vec2f startPosition;
    EPlayer(const std::string& tag, size_t id) : Entity(tag, id)
    {
        addComponent<CTransform>(Vec2f(300.0f, 300.0f), Vec2f(300.0f, 300.0f), 0);
        addComponent<CShape>(30, 12, sf::Color::Black, sf::Color::Red, 5);
        addComponent<CInput>();
        addComponent<CCircleCollider>(30);
    }
};
