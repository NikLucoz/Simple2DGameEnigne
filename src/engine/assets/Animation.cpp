#include "Animation.h"
#include <algorithm>
#include <SFML/Graphics/Texture.hpp>

Animation::Animation(const std::string& name, const sf::Texture& texture, size_t frameCount, int speed, bool isLoopable, size_t frameWidth, size_t frameHeight) : name(name), sprite_(texture), currentFrame(0), frameCount(frameCount), columnCount(0), speed(speed), animationTick(0.0f), bIsLoopable(isLoopable)
{
    if (frameCount > 0)
    {
        const size_t textureWidth = texture.getSize().x;
        const size_t textureHeight = texture.getSize().y;
        const size_t resolvedFrameWidth = frameWidth > 0 ? frameWidth : textureHeight;
        const size_t resolvedFrameHeight = frameHeight > 0 ? frameHeight : textureHeight;
        columnCount = resolvedFrameWidth > 0 ? textureWidth / resolvedFrameWidth : 0;

        if (columnCount == 0 || resolvedFrameHeight == 0) return;

        const size_t rowCount = (frameCount + columnCount - 1) / columnCount;
        const size_t availableRows = textureHeight / resolvedFrameHeight;
        if (rowCount > availableRows) return;

        size = Vector2<int>(static_cast<int>(resolvedFrameWidth), static_cast<int>(resolvedFrameHeight));
        setFrame(0);
    }
}

void Animation::update(float deltaTime)
{
    if (frameCount == 0 || speed <= 0) return;
    if (!bIsLoopable && hasEnded()) return;

    animationTick += deltaTime;
    const float frameDuration = 1.0f / static_cast<float>(speed);

    if (animationTick >= frameDuration)
    {
        animationTick = 0.0f;
        setFrame(static_cast<size_t>(currentFrame + 1));
    }
}

void Animation::setFrame(size_t frame)
{
    if (frameCount == 0 || columnCount == 0) return;

    if (bIsLoopable)
    {
        frame %= frameCount;
    }
    else
    {
        frame = std::min(frame, frameCount - 1);
    }

    currentFrame = static_cast<int>(frame);
    const int column = currentFrame % static_cast<int>(columnCount);
    const int row = currentFrame / static_cast<int>(columnCount);
    sprite_.setTextureRect(sf::IntRect({column * size.x, row * size.y}, {size.x, size.y}));
    sprite_.setOrigin({ size.x / 2.0f, size.y / 2.0f });
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
