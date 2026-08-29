#pragma once
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include "engine/entities/Entity.h"

class RenderSystem
{
public:
    void update(sf::RenderWindow& window, std::vector<std::shared_ptr<Entity>> entities, float deltaTime);
};
