#include "Engine.h"
#include <iostream>
#include "entities/EPlayer.h"
#include "engine/utils/debug_ui/DebugUI.h"
#include <SFML/System/Vector2.hpp>
#include "systems/EnemySpawnSystem.h"
#include "systems/CollisionSystem.h"
#include "systems/LifeSpanSystem.h"
#include "systems/MovementSystem.h"
#include "systems/RenderSystem.h"

GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string& title) 
    : window_(sf::VideoMode({width, height}), title), bIsRunning_(true) {
    window_.setFramerateLimit(60);
    debugUI_.Init(window_);
    std::cout << "Engine initialized: " << width << "x" << height << std::endl;
}

GameEngine::~GameEngine() {
    window_.close();
}

bool GameEngine::isOpen() const {
    return window_.isOpen();
}

void GameEngine::run() {
    std::cout << "Engine running... (Press ESC to exit)" << std::endl;
    
    player_ = EntityManager::getInstance().addEntity<EPlayer>("player");
    player_->getComponent<CTransform>().position = Vec2f(window_.getSize().x / 2, window_.getSize().y / 2);
    
    while (window_.isOpen() && bIsRunning_) {
        float deltaTime = clock_.restart().asSeconds();
        
        if (deltaTime > 0.1f) {
            deltaTime = 0.1f;
        }
        
        update(deltaTime);
        render(deltaTime);
    }
    
    std::cout << "Engine shutdown complete" << std::endl;
}

void GameEngine::update(float deltaTime) {
    handleEvents();
    EntityManager::getInstance().update();
    MovementSystem::getInstance().update(player_.get(), deltaTime);
    CollisionSystem::getInstance().update(window_.getSize(), deltaTime);
    EnemySpawnSystem::getInstance().update(deltaTime, window_);
    LifeSpanSystem::getInstance().update(deltaTime);
    debugUI_.Update(clock_, EntityManager::getInstance().getEntities());
}

void GameEngine::render(float deltaTime) {
    window_.clear(sf::Color::Black);
    
    drawTestGrid();
    RenderSystem::getInstance().update(window_, deltaTime);
    debugUI_.Render();
    window_.display();
}

// --------- EVENTS --------

void GameEngine::handleEvents() {
    while (auto event = window_.pollEvent()) {
        debugUI_.ProcessEvent(*event);

        if (const auto* closed = event->getIf<sf::Event::Closed>()) {
            handleEvent(*closed);
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            handleEvent(*keyPressed);
        }
        else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            handleEvent(*keyReleased);
        }
        else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (!debugUI_.GetAnyItemHovered()) {
                handleEvent(*mousePressed);
            }
        }
        else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            handleEvent(*mouseMoved);
        }
        else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            handleEvent(*resized);
        }
    }
}

void GameEngine::handleEvent(const sf::Event::Closed&) {
    window_.close();
    bIsRunning_ = false;
}

void GameEngine::handleEvent(const sf::Event::KeyPressed& event) {

    switch (event.code)
    {
        case sf::Keyboard::Key::W:
            player_.get()->getComponent<CInput>().bUp = true;
            break;
        case sf::Keyboard::Key::A:
            player_.get()->getComponent<CInput>().bLeft = true;
            break;
        case sf::Keyboard::Key::S:
            player_.get()->getComponent<CInput>().bDown = true;
            break;
        case sf::Keyboard::Key::D:
            player_.get()->getComponent<CInput>().bRight = true;
            break;
        default:
            break;
    }
}

void GameEngine::handleEvent(const sf::Event::KeyReleased& event) {
    switch (event.code)
    {
        case sf::Keyboard::Key::W:
            player_.get()->getComponent<CInput>().bUp = false;
            break;
        case sf::Keyboard::Key::A:
            player_.get()->getComponent<CInput>().bLeft = false;
            break;
        case sf::Keyboard::Key::S:
            player_.get()->getComponent<CInput>().bDown = false;
            break;
        case sf::Keyboard::Key::D:
            player_.get()->getComponent<CInput>().bRight = false;
            break;
        default:
            break;
    }
}

void GameEngine::handleEvent(const sf::Event::MouseButtonPressed& event) {

}

void GameEngine::handleEvent(const sf::Event::MouseMoved& event) {}

void GameEngine::handleEvent(const sf::Event::Resized& event) {
}

void GameEngine::drawTestGrid() {
    const float gridSpacing = 50.0f;
    auto windowSize = window_.getSize();
    sf::Color gridColor(50, 50, 50);
    
    for (float x = 0; x <= windowSize.x; x += gridSpacing) {
        sf::RectangleShape line({1.0f, static_cast<float>(windowSize.y)});
        line.setPosition({x, 0.0f});
        line.setFillColor(gridColor);
        window_.draw(line);
    }
    
    for (float y = 0; y <= windowSize.y; y += gridSpacing) {
        sf::RectangleShape line({static_cast<float>(windowSize.x), 1.0f});
        line.setPosition({0.0f, y});
        line.setFillColor(gridColor);
        window_.draw(line);
    }
}