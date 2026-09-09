#pragma once
#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "engine/Assets/Assets.h"
#include "engine/utils/debug_ui/DebugUI.h"
#include "scenes/Scene.h"

class GameEngine
{
    std::map<std::string, std::shared_ptr<Scene>> scenes_;
    sf::RenderWindow window_;
    sf::Clock clock_;
    std::string currentScene_;
    Assets* assets_ = nullptr;
    DebugUI debugUI_;
    bool bIsRunning_;
    
    void init();
    
    Scene* getCurrentScene()
    {
        return scenes_[currentScene_].get();
    }

public:
    GameEngine() = default;
    GameEngine(unsigned int width = 800, unsigned int height = 600, const std::string& title = "Game Engine");
    
    void run();
    void quit() const;
    void handleEvents();
    void update(float deltaTime);
    void render(float deltaTime);
    void changeScene(const std::string& sceneName, const std::shared_ptr<Scene>& scene);
    void sUserInput();
    
    Assets& getAssets() const;
    sf::RenderWindow& getWindow();
    void drawTestGrid(sf::RenderWindow& window);
};
