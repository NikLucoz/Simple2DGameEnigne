#include "RenderSystem.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

void RenderSystem::update(sf::RenderWindow& window, std::vector<std::shared_ptr<Entity>> entities, float deltaTime)
{
    for (std::shared_ptr<Entity>& ePtr : entities)
    {
        Entity& e = *ePtr;
        if (!e.hasComponent<CTransform>()) continue;
        CTransform& transform = e.getComponent<CTransform>();
        
        if (e.hasComponent<CShape>())
        {
            CShape& shape = e.getComponent<CShape>();
            sf::CircleShape sfShape(shape.radius_);
            Vec2f pos = transform.getPosition();
            sfShape.setPointCount(shape.point_count_);
            sfShape.setPosition(sf::Vector2f(pos.x, pos.y));
            sfShape.setOrigin({shape.radius_, shape.radius_});
            sfShape.setFillColor(shape.fillColor_);
            sfShape.setOutlineColor(shape.outlineColor_);
            sfShape.setOutlineThickness(shape.outlineThickness_);
            window.draw(sfShape);
        }
        
        if (e.hasComponent<CSprite>())
        {
            CSprite& sprite = e.getComponent<CSprite>();
            if (sprite.m_filepath.empty()) return;
    
            sf::Sprite sfSprite(sprite.getTexture());
            sf::Vector2u textureSize = sprite.getTexture().getSize();
            Vec2f desiredSize = sprite.getSize();
            
            Vec2f calculatedScale(
                desiredSize.x / textureSize.x,
                desiredSize.y / textureSize.y
            );
    
            sf::Vector2f finalScale = (calculatedScale * sprite.getScale()).toSFVector2();
            sfSprite.setScale(finalScale);
    
            sf::Vector2f spriteOrigin(
                textureSize.x / 2.0f,
                textureSize.y / 2.0f
            );
            sfSprite.setOrigin(spriteOrigin);
            sfSprite.setPosition(sf::Vector2f(transform.getPosition().x, transform.getPosition().y));
            sfSprite.setRotation(sf::degrees(transform.getRotation()));
            window.draw(sfSprite);
        }
    }
}
