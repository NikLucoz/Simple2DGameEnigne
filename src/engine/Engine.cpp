#include "Engine.h"

#include <imgui.h>
#include <iostream>
#include "entities/EPlayer.h"
#include "engine/utils/debug_ui/DebugUI.h"
#include <SFML/System/Vector2.hpp>

#include "components/CSpecialBullet.h"
#include "systems/EnemySpawnSystem.h"
#include "systems/CollisionSystem.h"
#include "systems/LifeSpanSystem.h"
#include "systems/MovementSystem.h"
#include "systems/RenderSystem.h"
#include "systems/ScoreSystem.h"

GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string& title)
    : window_(sf::VideoMode({width, height}), title), bIsRunning_(true), scoreText(font_)
{
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
    
    if (font_.openFromFile("game/assets/fonts/arial.ttf")) {
        scoreText.setFont(font_);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition({10.f, 10.f});
    }
    
    player_ = EntityManager::getInstance().addEntity<EPlayer>("player");
    Vec2f startPos = Vec2f(window_.getSize().x / 2, window_.getSize().y / 2);
    player_->getComponent<CTransform>().position = startPos;
    player_->startPosition = startPos;
    ScoreSystem::getInstance().setScore(0);
    
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
    MovementSystem::getInstance().update(player_.get(), deltaTime, clock_);
    CollisionSystem::getInstance().update(window_.getSize(), deltaTime);
    EnemySpawnSystem::getInstance().update(deltaTime, window_);
    LifeSpanSystem::getInstance().update(deltaTime);
    debugUI_.Update(clock_, EntityManager::getInstance().getEntities());
}

void GameEngine::render(float deltaTime) {
    window_.clear(sf::Color::Black);
    
    drawTestGrid();
    RenderSystem::getInstance().update(window_, deltaTime);
    scoreText.setString(sf::String("Score: ") + std::to_string(ScoreSystem::getInstance().getScore()));    
    window_.draw(scoreText);
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
    if (debugUI_.GetAnyItemHovered()) return;
    Entity* player = EntityManager::getInstance().getEntities("player").front().get();
    CTransform playerTransform = player->getComponent<CTransform>();
    
    if (event.button == sf::Mouse::Button::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window_);
        Vec2f shootDirection = Vec2f(mousePos.x, mousePos.y) - playerTransform.getPosition();
        
        auto e = EntityManager::getInstance().addEntity("bullet");
        e->addComponent<CTransform>(playerTransform.getPosition(), shootDirection.normalized() * 700, 0);
        e->addComponent<CShape>(12, 20, sf::Color::White, sf::Color::White, 0);
        e->addComponent<CCircleCollider>(12);
        e->addComponent<CLifespan>(6);
    }
    
    if (event.button == sf::Mouse::Button::Right)
    {
        float directions[4][2] = {
            {0.35f, -0.35f},
            {0.35f, 0.35f},
            {-0.35f, -0.35f},
            {-0.35f, 0.35f}
        };
        
        for (auto i = 0; i < 4; i++)
        {
            float dx = directions[i][0];
            float dy = directions[i][1];
            
            auto e = EntityManager::getInstance().addEntity("specialBullet");
            e->addComponent<CTransform>(playerTransform.getPosition(), Vec2f(dx,dy) * 300, 0);
            e->addComponent<CShape>(12, 20, sf::Color::White, sf::Color::White, 0);
            e->addComponent<CCircleCollider>(12);
            e->addComponent<CLifespan>(6);
            e->addComponent<CSpecialBullet>();
        }
    }
}

void GameEngine::handleEvent(const sf::Event::MouseMoved& event)
{
    
}

void GameEngine::handleEvent(const sf::Event::Resized& event) {
}

void GameEngine::drawTestGrid() {
    const float gridSpacing = 40.0f;
    auto windowSize = window_.getSize();

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
            window_.draw(square);
        }
    }
}