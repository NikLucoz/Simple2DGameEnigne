#pragma once
#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Animation.h"

class Assets
{
    std::map<std::string, sf::Texture> textures_;
    std::map<std::string, Animation> animations_;
    std::map<std::string, sf::Sound> sounds_;
    std::map<std::string, sf::SoundBuffer> soundBuffers_;
    std::map<std::string, sf::Font> fonts_;
public:
    Assets() = default;
    
    void addTexture(std::string name, std::string path);
    void addSound(std::string name, std::string path);
    void addAnimation(std::string name, Animation animation);
    void addFont(std::string name, std::string path);
    
    sf::Texture& getTexture(std::string name);
    sf::Sound& getSound(std::string name);
    sf::Font& getFont(std::string name);
    bool hasAnimation(const std::string& name) const;
    Animation& getAnimation(std::string name);
};
