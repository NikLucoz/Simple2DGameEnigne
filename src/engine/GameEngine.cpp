#include "GameEngine.h"
#include <algorithm>
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/scenes/Scene.h"
#include "entities/EntityManager.h"
#include "engine/actions/Action.h"
#include "engine/utils/assets/AssetsLoader.h"

GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string& title)
    : window_(sf::VideoMode({width, height}), title), bIsRunning_(false), assets_(new Assets()), scenes_()
{
    window_.setFramerateLimit(60);
    std::cout << "Engine initialized: " << width << "x" << height << std::endl;
}

void GameEngine::init()
{
    AssetsLoader::loadAssetsFromFile(*assets_, "game/assets/assets.cfg");
    debugUI_.Init(window_, *assets_);
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
    debugUI_.SetVisible(debugUI_.GetOptions().showDebugUI);
    DebugRuntimeInfo runtimeInfo;
    runtimeInfo.framesPerSecond = deltaTime > 0.0f ? 1.0f / deltaTime : 0.0f;
    runtimeInfo.windowSize = window_.getSize();
    runtimeInfo.currentScene = currentScene_;
    runtimeInfo.loadedScenes = getSceneNames();
    runtimeInfo.textures = assets_->getTextureNames();
    runtimeInfo.animations = assets_->getAnimationNames();
    runtimeInfo.sounds = assets_->getSoundNames();
    runtimeInfo.fonts = assets_->getFontNames();

    debugUI_.Update(sf::seconds(deltaTime), runtimeInfo, [currentScene]() {
        currentScene->sDebugUI();
    }, [this](const std::string& sceneName) {
        changeScene(sceneName);
    });

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
    debugUI_.Render();
    window_.display();
}

void GameEngine::quit()
{
    window_.close();
    bIsRunning_ = false;
}

void GameEngine::handleEvents()
{
    while (auto event = window_.pollEvent()) {
        debugUI_.ProcessEvent(*event);
        
        if (event->is<sf::Event::Closed>()) {
            quit();
        }
        
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::F3 || !debugUI_.WantsKeyboardInput()) {
                handleUserKeyboardInputEvent(keyPressed->code, "pressed");
            }
        }
        
        if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            if (keyReleased->code != sf::Keyboard::Key::F3 && !debugUI_.WantsKeyboardInput()) {
                handleUserKeyboardInputEvent(keyReleased->code, "released");
            }
        }
        
        if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (!debugUI_.WantsMouseInput()) {
                handleUserMouseInputEvent(mouseButtonPressed->button, "pressed");
            }
        }
        
        if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (!debugUI_.WantsMouseInput()) {
                handleUserMouseInputEvent(mouseButtonReleased->button, "released");
            }
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

void GameEngine::changeScene(const std::string& sceneName)
{
    if (scenes_.find(sceneName) == scenes_.end()) {
        throw std::invalid_argument("Scene '" + sceneName + "' is not registered");
    }

    if (currentScene_ == sceneName) {
        std::cout << "Scene '" << sceneName << "' is already the current scene." << std::endl;
        return;
    }

    if (!currentScene_.empty()) {
        getCurrentScene()->destroy();
    }

    currentScene_ = sceneName;
    getCurrentScene()->init();
}

Assets& GameEngine::getAssets() const
{
    return *assets_;
}

sf::RenderWindow& GameEngine::getWindow()
{
    return window_;
}

const std::string& GameEngine::getCurrentSceneName() const
{
    return currentScene_;
}

std::vector<std::string> GameEngine::getSceneNames() const
{
    std::vector<std::string> names;
    for (const auto& [name, scene] : scenes_) names.push_back(name);
    return names;
}

void GameEngine::sUserInput()
{
    
}

void GameEngine::drawTestGrid(sf::RenderWindow& window) {
    const float gridSpacing = 64.0f;
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