#include "RenderSystem.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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
    }
}
