#include "CSprite.h"
#include <SFML/Graphics/Texture.hpp>

CSprite::CSprite(Vector2 size, Vector2 origin, Vector2 scale, const std::string& filepath, sf::Color color)
{
    m_filepath = filepath;
    m_size = size;
    m_origin = origin;
    m_color = color;
    m_scale = scale;
    
    if (filepath.empty()) throw std::invalid_argument("CSprite: filepath is empty");
    
    if (!m_texture_.loadFromFile(filepath)) throw std::runtime_error("CSprite: failed to load \"" + m_filepath + "\"");
}

Vector2 CSprite::getSize()
{
    return m_size;
}

Vector2 CSprite::getOrigin()
{
    return m_origin;
}

Vector2 CSprite::getScale()
{
    return m_scale;
}

sf::Texture& CSprite::getTexture()
{
    return m_texture_;
}