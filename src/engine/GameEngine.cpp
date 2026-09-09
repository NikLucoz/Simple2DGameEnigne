#include "GameEngine.h"
#include <algorithm>
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/scenes/Scene.h"
#include "entities/EntityManager.h"
#include "scenes/ScenePlay.h"

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
    auto scene = std::make_shared<ScenePlay>(this, 1.0f);
    scenes_["gameplay_scene"] = scene;
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
    while (const std::optional event = window_.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window_.close();
            bIsRunning_ = false;
        }
        // TODO: add extra events
    }
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