#pragma once

#include "Component.h"
#include "engine/utils/math/Vector2.h"

class CTransform : public Component
{
public:
    Vector2 position = {0.0f, 0.0f};
    Vector2 velocity = {0.0f, 0.0f};

    CTransform() = default;
    CTransform(const Vector2& position, const Vector2& velocity) 
        : position(position), velocity(velocity) {}
};