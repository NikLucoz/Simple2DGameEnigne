#include "Animation.h"
#include <algorithm>
#include <SFML/Graphics/Texture.hpp>

Animation::Animation(const std::string& name, const sf::Texture& texture, size_t frameCount, int speed, bool isLoopable)
    : name(name), sprite_(texture), currentFrame(0), frameCount(frameCount), speed(speed), gameFrame(0), bIsLoopable(isLoopable)
{
    if (frameCount > 0)
    {
        size = Vector2<int>(texture.getSize().x / frameCount, texture.getSize().y);
        setFrame(0);
    }
}

void Animation::update()
{
    if (frameCount == 0 || speed <= 0) return;
    if (!bIsLoopable && hasEnded()) return;

    ++gameFrame;
    const size_t updatedGameFrame = gameFrame;
    setFrame(updatedGameFrame / static_cast<size_t>(speed));
    gameFrame = updatedGameFrame;
}

void Animation::setFrame(size_t frame)
{
    if (frameCount == 0) return;

    if (bIsLoopable)
    {
        frame %= frameCount;
    }
    else
    {
        frame = std::min(frame, frameCount - 1);
    }

    currentFrame = static_cast<int>(frame);
    gameFrame = frame * static_cast<size_t>(std::max(speed, 0));
    sprite_.setTextureRect(sf::IntRect({currentFrame * size.x, 0}, {size.x, size.y}));
}

bool Animation::hasEnded() const
{
    return frameCount > 0 && currentFrame >= static_cast<int>(frameCount - 1);
}

sf::Sprite& Animation::getSprite()
{
    return sprite_;
}

const Vector2<int>& Animation::getSize() const 
{
    return size;
}

const std::string &Animation::getName() const
{
    return name;
}

const bool Animation::getIsLoopable() const 
{
    return bIsLoopable;
}

void Animation::setIsLoopable(bool value) 
{
    bIsLoopable = value;
}