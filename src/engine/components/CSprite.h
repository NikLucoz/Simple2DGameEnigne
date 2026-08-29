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
    Vector2 m_size;
    Vector2 m_origin;
    Vector2 m_scale;
    sf::Color m_color;
    std::string m_filepath;

    CSprite() : m_size(0, 0), m_origin(0, 0), m_scale(1, 1), 
                m_color(sf::Color::White), m_filepath("") {}
    CSprite(Vector2 size, Vector2 origin, Vector2 scale, const std::string& filepath, sf::Color color = sf::Color::White);
    Vector2 getSize();
    Vector2 getOrigin();
    Vector2 getScale();
    sf::Texture& getTexture();
};
