#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <type_traits>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
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
    
    
    Scene* getCurrentScene()
    {
        return scenes_[currentScene_].get();
    }
    
    void handleUserKeyboardInputEvent(sf::Keyboard::Key keyCode, const std::string& actionType);
    void handleUserMouseInputEvent(sf::Mouse::Button button, const std::string& actionType);
    
    public:
    GameEngine() = default;
    GameEngine(unsigned int width = 800, unsigned int height = 600, const std::string& title = "Game Engine");
    
    void init();
    void run();
    void quit();
    void handleEvents();
    void update(float deltaTime);
    void render(float deltaTime);
    void changeScene(const std::string& sceneName);
    void sUserInput();

    template <typename T, typename... Args>
    void registerScene(const std::string& sceneName, Args&&... args)
    {
        static_assert(std::is_base_of_v<Scene, T>, "T must derive from Scene");

        scenes_[sceneName] = std::make_shared<T>(
            this,
            std::forward<Args>(args)...
        );
    }
    
    Assets& getAssets() const;
    sf::RenderWindow& getWindow();
    const std::string& getCurrentSceneName() const;
    std::vector<std::string> getSceneNames() const;
    DebugOptions& getDebugOptions() { return debugUI_.GetOptions(); }
    const DebugOptions& getDebugOptions() const { return debugUI_.GetOptions(); }
    void drawTestGrid(sf::RenderWindow& window);
};
