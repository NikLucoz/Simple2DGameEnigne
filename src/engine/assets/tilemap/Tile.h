#pragma once
#include <cstddef>
#include <string>
#include <utility>
#include <SFML/Graphics/Rect.hpp>

class Tile {
    std::size_t id_ = 0;
    std::string tilesetName_;
    sf::IntRect textureRect_;
    std::string animationName_;
    bool solid_ = false;

public:
    Tile() = default;

    Tile(std::size_t id,
                   std::string tilesetName,
                   sf::IntRect textureRect,
                   std::string animationName = {},
                   bool solid = false)
        : id_(id),
          tilesetName_(std::move(tilesetName)),
          textureRect_(textureRect),
          animationName_(std::move(animationName)),
          solid_(solid)
    {}

    std::size_t getId() const { return id_; }
    const std::string& getTilesetName() const { return tilesetName_; }
    const sf::IntRect& getTextureRect() const { return textureRect_; }
    const std::string& getAnimationName() const { return animationName_; }
    bool isSolid() const { return solid_; }
};