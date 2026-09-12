#include "Camera.h"

#include <algorithm>
#include <cmath>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Angle.hpp"

Camera::Camera(Vector2<float> initialViewSize, Vector2<float> initialPosition)
    : cameraView_(),
      targetPos_(initialPosition),
      currentPos_(initialPosition),
      baseViewSize_(initialViewSize),
      worldBounds_(),
      viewport_({0.0f, 0.0f}, {1.0f, 1.0f}),
      zoom_(1.0f),
      rotation_(0.0f),
      followSmoothing_(0.0f),
      bHasTarget_(false),
      bHasWorldBounds_(false)
{
    cameraView_.setCenter(currentPos_.toSFVector2());
    cameraView_.setSize(baseViewSize_.toSFVector2());
    cameraView_.setRotation(sf::degrees(rotation_));
    cameraView_.setViewport(viewport_);
}

void Camera::setPosition(Vector2<float> position)
{
    currentPos_ = position;
    targetPos_ = position;
    cameraView_.setCenter(currentPos_.toSFVector2());
}

Vector2<float> Camera::getPosition()
{
    return currentPos_;
}

void Camera::setTarget(Vector2<float> position)
{
    targetPos_ = position;
    bHasTarget_ = true;
}

void Camera::clearTarget()
{
    bHasTarget_ = false;
}

void Camera::setFollowSmoothing(float smooth) 
{
    followSmoothing_ = smooth;
}

void Camera::setZoom(float zoom)
{
    zoom_ = std::max(zoom, 0.01f);
}

float Camera::getZoom()
{
    return zoom_;
}

void Camera::setViewSize(Vector2<float> viewSize)
{
    baseViewSize_ = viewSize;
    cameraView_.setSize((baseViewSize_ * zoom_).toSFVector2());
}

sf::Vector2f Camera::getViewSize() const
{
    return cameraView_.getSize();
}

void Camera::setRotation(float rotation)
{
    rotation_ = rotation;
    cameraView_.setRotation(sf::degrees(rotation_));
}

float Camera::getRotation()
{
    return rotation_;
}

void Camera::setViewport(sf::FloatRect viewportRectangle)
{
    viewport_ = viewportRectangle;
    cameraView_.setViewport(viewport_);
}

sf::FloatRect Camera::getViewport() const
{
    return viewport_;
}

void Camera::setWorldBounds(sf::FloatRect worldBounds)
{
    worldBounds_ = worldBounds;
    bHasWorldBounds_ = true;
}

sf::FloatRect Camera::getWorldBounds()
{
    return worldBounds_;
}

void Camera::clearWorldBounds()
{
    bHasWorldBounds_ = false;
}

void Camera::update(float deltaTime)
{
    if (bHasTarget_)
    {
        if (followSmoothing_ <= 0.0f)
        {
            currentPos_ = targetPos_;
        }
        else
        {
            const float blend = 1.0f - std::exp(-followSmoothing_ * deltaTime);
            currentPos_ = currentPos_ + (targetPos_ - currentPos_) * blend;
        }
    }

    cameraView_.setSize((baseViewSize_ * zoom_).toSFVector2());

    if (bHasWorldBounds_)
    {
        const sf::Vector2f viewSize = cameraView_.getSize();
        const float minX = worldBounds_.position.x + viewSize.x * 0.5f;
        const float maxX = worldBounds_.position.x + worldBounds_.size.x - viewSize.x * 0.5f;
        const float minY = worldBounds_.position.y + viewSize.y * 0.5f;
        const float maxY = worldBounds_.position.y + worldBounds_.size.y - viewSize.y * 0.5f;

        if (worldBounds_.size.x <= viewSize.x)
            currentPos_.x = worldBounds_.position.x + worldBounds_.size.x * 0.5f;
        else
            currentPos_.x = std::clamp(currentPos_.x, minX, maxX);

        if (worldBounds_.size.y <= viewSize.y)
            currentPos_.y = worldBounds_.position.y + worldBounds_.size.y * 0.5f;
        else
            currentPos_.y = std::clamp(currentPos_.y, minY, maxY);
    }

    cameraView_.setCenter(currentPos_.toSFVector2());
    cameraView_.setRotation(sf::degrees(rotation_));
}

void Camera::applyTo(sf::RenderWindow& window) const
{
    window.setView(cameraView_);
}

void Camera::restoreDefaultView(sf::RenderWindow& window) const
{
    window.setView(window.getDefaultView());
}

sf::Vector2f Camera::screenToWorld(sf::Vector2i screenPosition, const sf::RenderWindow& window) const
{
    return window.mapPixelToCoords(screenPosition, cameraView_);
}

sf::Vector2i Camera::worldToScreen(sf::Vector2f worldPosition, const sf::RenderWindow& window) const
{
    return window.mapCoordsToPixel(worldPosition, cameraView_);
}
