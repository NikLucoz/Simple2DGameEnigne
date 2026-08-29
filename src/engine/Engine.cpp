#include "Engine.h"

#include "../../game/src/entities/EPlayer.h"
#include "engine/utils/debug_ui/DebugUI.h"

GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string& title)
    : window(sf::VideoMode({width, height}), title), isRunning(true) {
    window.setFramerateLimit(60);
    m_debugUI.Init(window);
    std::cout << "Engine initialized: " << width << "x" << height << std::endl;
}

GameEngine::~GameEngine() {
    window.close();
}

bool GameEngine::isOpen() const {
    return window.isOpen();
}

void GameEngine::run() {
    std::cout << "Engine running... (Press ESC to exit)" << std::endl;
    
    m_entityManager.addEntity<EPlayer>("player");
    
    while (window.isOpen() && isRunning) {
        float deltaTime = clock.restart().asSeconds();
        
        if (deltaTime > 0.1f) {
            deltaTime = 0.1f;
        }
        
        handleEvents();
        update(deltaTime);
        render(deltaTime);
    }
    
    std::cout << "Engine shutdown complete" << std::endl;
}

void GameEngine::update(float deltaTime) {
    m_entityManager.update();
    m_debugUI.Update(clock, m_entityManager.getEntities());
}


void GameEngine::render(float deltaTime) {
    window.clear(sf::Color::Black);
    
    drawTestGrid();
    m_renderSystem.update(window, m_entityManager.getEntities(), deltaTime);
    m_debugUI.Render();
    
    window.display();
}

// --------- EVENTS --------

void GameEngine::handleEvents() {
    while (auto event = window.pollEvent()) {
        m_debugUI.ProcessEvent(*event);

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
            if (!m_debugUI.GetAnyItemHovered()) {
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
    std::cout << "Window closed" << std::endl;
    window.close();
    isRunning = false;
}

void GameEngine::handleEvent(const sf::Event::KeyPressed& event) {
    std::cout << "Key pressed: " << static_cast<int>(event.code) << std::endl;
}

void GameEngine::handleEvent(const sf::Event::KeyReleased& event) {
    std::cout << "Key released: " << static_cast<int>(event.code) << std::endl;
}

void GameEngine::handleEvent(const sf::Event::MouseButtonPressed& event) {
    std::cout << "Mouse pressed at: (" << event.position.x << ", " << event.position.y << ")" << std::endl;
    auto e = m_entityManager.addEntity("test");
    e->addComponent<CTransform>(Vec2f{static_cast<float>(event.position.x), static_cast<float>(event.position.y)}, Vec2f(0,0), 0.0f);
    e->addComponent<CSprite>(Vec2f(200, 300), Vec2f(0,0), Vec2f(1,1), "game/assets/sprites/Fireball.png");
}

void GameEngine::handleEvent(const sf::Event::MouseMoved& event) {}

void GameEngine::handleEvent(const sf::Event::Resized& event) {
    std::cout << "Window resized to: " << event.size.x << "x" << event.size.y << std::endl;
}

void GameEngine::drawTestGrid() {
    const float gridSpacing = 50.0f;
    auto windowSize = window.getSize();
    sf::Color gridColor(50, 50, 50);
    
    for (float x = 0; x <= windowSize.x; x += gridSpacing) {
        sf::RectangleShape line({1.0f, static_cast<float>(windowSize.y)});
        line.setPosition({x, 0.0f});
        line.setFillColor(gridColor);
        window.draw(line);
    }
    
    for (float y = 0; y <= windowSize.y; y += gridSpacing) {
        sf::RectangleShape line({static_cast<float>(windowSize.x), 1.0f});
        line.setPosition({0.0f, y});
        line.setFillColor(gridColor);
        window.draw(line);
    }
}