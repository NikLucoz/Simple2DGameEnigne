#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <engine/utils/math/Vector2.h>

class Animation
{ 
    sf::Sprite sprite_;
    size_t frameCount;
    float animationTick;
    int currentFrame;
    int speed;
    Vector2<int> size;
    std::string name;
    bool bIsLoopable;
public:
    Animation(const std::string& name, const sf::Texture& texture, size_t frameCount, int speed, bool isLoopable);
    void update(float deltaTime);
    void setFrame(size_t frame);
    bool hasEnded() const;
    sf::Sprite& getSprite();
    const std::string& getName() const;
    const Vector2<int>& getSize() const;
    const bool getIsLoopable() const;
    void setIsLoopable(bool value);
};
