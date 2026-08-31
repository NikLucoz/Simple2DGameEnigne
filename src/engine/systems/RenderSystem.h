#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class RenderSystem
{
    RenderSystem() = default;
public:
    bool bIsActive_ = true;
    bool bDrawDebug_ = false;
    static RenderSystem& getInstance();
    void update(sf::RenderWindow& window, float deltaTime);
};
