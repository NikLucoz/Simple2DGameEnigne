#pragma once
#include <string>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp> 
#include "engine/utils/math/Vector2.h"
#include "Component.h"

class CSprite : public Component
{
    sf::Texture m_texture_;
public:
    Vec2f m_size;
    Vec2f m_origin;
    Vec2f m_scale;
    sf::Color m_color;
    
    CSprite() = default;
    CSprite(sf::Texture texture, Vec2f size, Vec2f origin, Vec2f scale, sf::Color color);
    Vec2f getSize();
    Vec2f getOrigin();
    Vec2f getScale();
    sf::Texture& getTexture();
};