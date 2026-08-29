#include "RenderSystem.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

void RenderSystem::update(sf::RenderWindow& window, std::vector<std::shared_ptr<Entity>> entities, float deltaTime)
{
    for (std::shared_ptr<Entity>& ePtr : entities)
    {
        Entity& e = *ePtr;
        if (!e.has<CTransform>()) continue;
        CTransform& transform = e.get<CTransform>();
        
        if (e.has<CCircleShape>())
        {
            CCircleShape& circle = e.get<CCircleShape>();
            sf::CircleShape sfCircle(circle.radius);
            Vector2 pos = transform.getPosition();
            sfCircle.setPosition(sf::Vector2f(pos.x, pos.y));
            sfCircle.setFillColor(circle.fillColor);
            sfCircle.setOutlineColor(circle.OutlineColor);
            sfCircle.setOutlineThickness(circle.OutlineThickness);
            window.draw(sfCircle);
        }
        else if (e.has<CPolygonShape>())
        {
            
        }
        else if (e.has<CRectangleShape>())
        {
            
        }
        
        if (e.has<CSprite>())
        {
            CSprite& sprite = e.get<CSprite>();
            if (sprite.m_filepath.empty()) return;
    
            sf::Sprite sfSprite(sprite.getTexture());
            sf::Vector2u textureSize = sprite.getTexture().getSize();
            Vector2 desiredSize = sprite.getSize();
            
            Vector2 calculatedScale(
                desiredSize.x / textureSize.x,
                desiredSize.y / textureSize.y
            );
    
            sf::Vector2f finalScale = (calculatedScale * sprite.getScale()).toSFVector2();
            sfSprite.setScale(finalScale);
    
            sfSprite.setOrigin(sprite.getOrigin().toSFVector2());
            sfSprite.setPosition(sf::Vector2f(transform.getPosition().x, transform.getPosition().y));
            sfSprite.setRotation(sf::degrees(transform.getRotation()));
            window.draw(sfSprite);
        }
    }
}
