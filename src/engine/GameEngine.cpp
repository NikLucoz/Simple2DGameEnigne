#include "GameEngine.h"
#include <algorithm>
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/scenes/Scene.h"
#include "entities/EntityManager.h"
#include "scenes/ScenePlay.h"
#include "engine/actions/Action.h"
#include "engine/scenes/MainMenuScene.h"

GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string& title)
    : window_(sf::VideoMode({width, height}), title), bIsRunning_(false), assets_(new Assets()), scenes_()
{
    window_.setFramerateLimit(60);
    debugUI_.Init(window_);
    init();
    std::cout << "Engine initialized: " << width << "x" << height << std::endl;
}

void GameEngine::init()
{
    assets_->addFont("arial", "game/assets/fonts/arial.ttf");
    scenes_["main_menu_scene"] = std::make_shared<MainMenuScene>(this);
    scenes_["gameplay_scene"] = std::make_shared<ScenePlay>(this, 1.0f);
    currentScene_ = scenes_.begin()->first;
}

void GameEngine::run()
{
    std::cout << "Engine running" << std::endl;
    bIsRunning_ = true;
    try
    {
        while (window_.isOpen() && bIsRunning_) {
            float deltaTime = clock_.restart().asSeconds();
            deltaTime = std::min(deltaTime, 0.1f);
            update(deltaTime);
        }
    } catch (const std::exception& e)
    {
        std::cout << "Engine error: " << e.what() << std::endl;
    }
    
    std::cout << "Engine shutdown complete" << std::endl;
}

void GameEngine::update(float deltaTime)
{
    Scene* currentScene = getCurrentScene();
    if (currentScene == nullptr) {
        throw std::runtime_error("Current scene not initialized");
    }
    
    EntityManager::getInstance().update();
    handleEvents();
    currentScene->update(deltaTime);
    //debugUI_.Update(clock_);
    render(deltaTime);
}

void GameEngine::render(float deltaTime) {
    Scene* currentScene = getCurrentScene();
    if (currentScene == nullptr) {
        throw std::runtime_error("Current scene not initialized");
    }
    
    window_.clear(sf::Color::Black);
    drawTestGrid(window_);
    currentScene->sRender(deltaTime);
    //debugUI_.Render();
    window_.display();
}

void GameEngine::quit() const
{
    //window_.close();
    //bIsRunning_ = false;
}

void GameEngine::handleEvents()
{
    while (auto event = window_.pollEvent()) {
        debugUI_.ProcessEvent(*event);
        
        if (event->is<sf::Event::Closed>()) {
            window_.close();
            bIsRunning_ = false;
        }
        
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            handleUserKeyboardInputEvent(keyPressed->code, "pressed");
        }
        
        if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            handleUserKeyboardInputEvent(keyReleased->code, "released");
        }
        
        if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            handleUserMouseInputEvent(mouseButtonPressed->button, "pressed");
        }
        
        if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
            handleUserMouseInputEvent(mouseButtonReleased->button, "released");
        }
    }
}

void GameEngine::handleUserKeyboardInputEvent(sf::Keyboard::Key keyCode, const std::string& actionType) {
    const InputBinding binding {
        InputDevice::Keyboard,
        static_cast<int>(keyCode)
    };

    auto& actionMap = getCurrentScene()->getActionMap();
    auto action = actionMap.find(binding);

    if (action == actionMap.end())
        return;

    getCurrentScene()->doAction(Action(action->second, actionType));
}

void GameEngine::handleUserMouseInputEvent(sf::Mouse::Button button, const std::string& actionType) {
    const InputBinding binding {
        InputDevice::MouseButton,
        static_cast<int>(button)
    };

    auto& actionMap = getCurrentScene()->getActionMap();
    auto action = actionMap.find(binding);

    if (action == actionMap.end())
        return;

    getCurrentScene()->doAction(Action(action->second, actionType));
}

void GameEngine::changeScene(const std::string& sceneName, const std::shared_ptr<Scene>& scene)
{
    if (scenes_.find(sceneName) == scenes_.end())
    {
        scenes_[sceneName] = scene;
    }
    currentScene_ = sceneName;
}

Assets& GameEngine::getAssets() const
{
    return *assets_;
}

sf::RenderWindow& GameEngine::getWindow()
{
    return window_;
}

void GameEngine::sUserInput()
{
    
}

void GameEngine::drawTestGrid(sf::RenderWindow& window) {
    const float gridSpacing = 40.0f;
    auto windowSize = window.getSize();

    const sf::Color blue(28, 27, 30);
    const sf::Color dark_blue(17, 16, 21);

    for (float y = 0; y < windowSize.y; y += gridSpacing) {
        for (float x = 0; x < windowSize.x; x += gridSpacing) {
            sf::RectangleShape square({gridSpacing, gridSpacing});
            square.setPosition({x, y});

            // Checkerboard pattern
            const int col = static_cast<int>(x / gridSpacing);
            const int row = static_cast<int>(y / gridSpacing);

            square.setFillColor((col + row) % 2 == 0 ? blue : dark_blue);
            window.draw(square);
        }
    }
}