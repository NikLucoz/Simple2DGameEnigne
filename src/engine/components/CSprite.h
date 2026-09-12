#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp> 
#include "SFML/Graphics/Sprite.hpp"
#include "engine/utils/math/Vector2.h"
#include "Component.h"
#include <optional>

class CSprite : public Component
{
    std::optional<sf::Sprite> sprite_;
public:
    Vec2f m_size;
    Vec2f m_origin;
    Vec2f m_scale;
    sf::Color m_color;
    
    CSprite();
    CSprite(const sf::Texture& texture, Vec2f size, Vec2f origin, Vec2f scale, sf::Color color = sf::Color::White);
    Vec2f getSize();
    Vec2f getOrigin();
    Vec2f getScale();
    const sf::Texture& getTexture();
    sf::Sprite& getSprite();
};