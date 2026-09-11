#pragma once
#include "Component.h"
#include <engine/assets/Animation.h>

class CAnimatedSprite : public Component 
{
public:
    Animation* animation = nullptr;

    CAnimatedSprite() = default;

    explicit CAnimatedSprite(Animation& animation): animation(&animation)
    {
    }
};