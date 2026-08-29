#include "CSprite.h"
#include <SFML/Graphics/Texture.hpp>

CSprite::CSprite(Vec2f size, Vec2f origin, Vec2f scale, const std::string& filepath, sf::Color color)
{
    m_filepath = filepath;
    m_size = size;
    m_origin = origin;
    m_color = color;
    m_scale = scale;
    
    if (filepath.empty()) throw std::invalid_argument("CSprite: filepath is empty");
    
    if (!m_texture_.loadFromFile(filepath)) throw std::runtime_error("CSprite: failed to load \"" + m_filepath + "\"");
}

Vec2f CSprite::getSize()
{
    return m_size;
}

Vec2f CSprite::getOrigin()
{
    return m_origin;
}

Vec2f CSprite::getScale()
{
    return m_scale;
}

sf::Texture& CSprite::getTexture()
{
    return m_texture_;
}