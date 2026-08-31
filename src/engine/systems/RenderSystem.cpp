#include "RenderSystem.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../entities/EntityManager.h"

RenderSystem& RenderSystem::getInstance()
{
    static RenderSystem renderSystem;
    return renderSystem;
}

void RenderSystem::update(sf::RenderWindow& window, float deltaTime)
{
    if (!bIsActive_) return;

    for (std::shared_ptr<Entity>& ePtr : EntityManager::getInstance().getEntities())
    {
        Entity& e = *ePtr;
        if (!e.hasComponent<CTransform>()) continue;
        CTransform& transform = e.getComponent<CTransform>();
        Vec2f pos = transform.getPosition();
        
        if (e.hasComponent<CShape>())
        {
            CShape& cShape = e.getComponent<CShape>();
            cShape.getShape()->setPointCount(cShape.point_count_);
            cShape.getShape()->setPosition(sf::Vector2f(pos.x, pos.y));
            cShape.getShape()->setRotation(sf::degrees(transform.getRotation()));
            cShape.getShape()->setOrigin({cShape.radius_, cShape.radius_});
            cShape.getShape()->setFillColor(cShape.fillColor_);
            cShape.getShape()->setOutlineColor(cShape.outlineColor_);
            cShape.getShape()->setOutlineThickness(cShape.outlineThickness_);
            window.draw(*cShape.getShape());
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

        if (bDrawDebug_)
        {
            if (e.hasComponent<CCircleCollider>())
            {
                CCircleCollider& c = e.getComponent<CCircleCollider>();
                sf::CircleShape sfShape(c.radius_);
                sfShape.setPointCount(20);
                sfShape.setPosition(sf::Vector2f(pos.x, pos.y));
                sfShape.setOrigin({c.radius_, c.radius_});
                sfShape.setFillColor(sf::Color::Transparent);
                sfShape.setOutlineColor(sf::Color::Green);
                sfShape.setOutlineThickness(2);
                window.draw(sfShape);

            }
        }
    }
}
