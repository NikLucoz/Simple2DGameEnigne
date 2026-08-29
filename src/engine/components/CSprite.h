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
    std::string m_filepath;

    CSprite() : m_size(0, 0), m_origin(0, 0), m_scale(1, 1), 
                m_color(sf::Color::White), m_filepath("") {}
    CSprite(Vec2f size, Vec2f origin, Vec2f scale, const std::string& filepath, sf::Color color = sf::Color::White);
    Vec2f getSize();
    Vec2f getOrigin();
    Vec2f getScale();
    sf::Texture& getTexture();
};
