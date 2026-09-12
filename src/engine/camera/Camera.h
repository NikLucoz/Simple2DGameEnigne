#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"
#include "engine/utils/math/Vector2.h"

class Camera {
    sf::View cameraView_;
    
    Vector2<float> targetPos_;
    Vector2<float> currentPos_;
    Vector2<float> baseViewSize_;

    sf::FloatRect worldBounds_;
    sf::FloatRect viewport_;    

    float zoom_;
    float rotation_;
    float followSmoothing_;

    bool bHasTarget_;
    bool bHasWorldBounds_;
public:
    Camera(Vector2<float> initialViewSize, Vector2<float> initialPosition);
    void setPosition(Vector2<float> pos);
    Vector2<float> getPosition();
    
    void setTarget(Vector2<float> position);
    void clearTarget();
    
    void setFollowSmoothing(float smooth);

    void setZoom(float zoom);
    float getZoom();

    void setViewSize(Vector2<float> viewSize);
    sf::Vector2f getViewSize() const;

    void setRotation(float rotation);
    float getRotation();

    void setViewport(sf::FloatRect viewportRectangle);
    sf::FloatRect getViewport() const;

    void setWorldBounds(sf::FloatRect worldBounds);
    sf::FloatRect getWorldBounds();
    void clearWorldBounds();

    void update(float deltaTime);

    void applyTo(sf::RenderWindow& window) const;

    void restoreDefaultView(sf::RenderWindow& window) const;

    sf::Vector2f screenToWorld(
        sf::Vector2i screenPosition,
        const sf::RenderWindow& window
    ) const;

    sf::Vector2i worldToScreen(
        sf::Vector2f worldPosition,
        const sf::RenderWindow& window
    ) const;
};