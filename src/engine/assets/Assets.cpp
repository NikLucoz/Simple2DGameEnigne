#include "Assets.h"
#include "Animation.h"
#include <stdexcept>

void Assets::addTexture(std::string name, std::string path)
{
    sf::Texture texture;
    if (texture.loadFromFile(path))
    {
        textures_[name] = texture;
    }
}

void Assets::addSound(std::string name, std::string path)
{
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(path))
    {
        soundBuffers_[name] = std::move(buffer);
        // Create the Sound only after the buffer is stored
        sounds_.emplace(name, soundBuffers_[name]); // constructs sf::Sound(buffer)
    }
}

void Assets::addAnimation(std::string name, Animation animation)
{
    animations_.insert_or_assign(std::move(name), std::move(animation));
}

void Assets::addFont(std::string name, std::string path)
{
    sf::Font font;
    if (font.openFromFile(path)) {
        fonts_[name] = font;
    }
}

sf::Texture& Assets::getTexture(std::string name)
{
    return textures_[name];
}

sf::Sound& Assets::getSound(std::string name)
{
    auto it = sounds_.find(name);
    if (it == sounds_.end())
    {
        throw std::runtime_error("Sound not found: " + name);
    }
    return it->second;
}

sf::Font& Assets::getFont(std::string name)
{
    return fonts_[name];
}

bool Assets::hasAnimation(const std::string& name) const
{
    return animations_.find(name) != animations_.end();
}

Animation& Assets::getAnimation(std::string name)
{
    auto it = animations_.find(name);
    if (it == animations_.end())
    {
        throw std::runtime_error("Animation not found: " + name);
    }

    return it->second;
}
