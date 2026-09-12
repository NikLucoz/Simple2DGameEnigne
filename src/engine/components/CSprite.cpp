#include "CSprite.h"
#include "SFML/Graphics/Sprite.hpp"
#include <SFML/Graphics/Texture.hpp>

CSprite::CSprite(sf::Texture texture, Vec2f size, Vec2f origin, Vec2f scale, sf::Color color) : sprite_(sf::Sprite(texture))
{
    m_size = size;
    m_origin = origin;
    m_color = color;
    m_scale = scale;
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

sf::Sprite& CSprite::getSprite() {
    return sprite_;
}

const sf::Texture& CSprite::getTexture()
{
    return sprite_.getTexture();
}