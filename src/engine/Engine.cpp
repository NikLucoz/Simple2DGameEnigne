#include "Engine.h"

GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string& title)
    : window(sf::VideoMode({width, height}), title), isRunning(true) {
    window.setFramerateLimit(60);
    std::cout << "Engine initialized: " << width << "x" << height << std::endl;
}

GameEngine::~GameEngine() {
    window.close();
}

bool GameEngine::isOpen() const {
    return window.isOpen();
}

void GameEngine::handleEvents() {
    // SFML 3.x: pollEvent() returns std::optional<sf::Event>
    while (auto event = window.pollEvent()) {
        // Access the event data directly
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
            handleEvent(*mousePressed);
        }
        else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            handleEvent(*mouseMoved);
        }
        else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            handleEvent(*resized);
        }
    }
}

void GameEngine::update(float deltaTime) {
    // ESC to exit
    m_entityManager.update();
}

void GameEngine::render() {
    window.clear(sf::Color::Black);
    
    // Draw test grid
    drawTestGrid();
    
    window.display();
}

void GameEngine::run() {
    std::cout << "Engine running... (Press ESC to exit)" << std::endl;
    
    while (window.isOpen() && isRunning) {
        float deltaTime = clock.restart().asSeconds();
        
        // Cap deltaTime
        if (deltaTime > 0.1f) {
            deltaTime = 0.1f;
        }
        m_entityManager.update();
        handleEvents();
        update(deltaTime);
        render();
    }
    
    std::cout << "Engine shutdown complete" << std::endl;
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
    e->add<CTransform>(Vector2{static_cast<float>(event.position.x), static_cast<float>(event.position.y)}, Vector2(0,0));
}

void GameEngine::handleEvent(const sf::Event::MouseMoved& event) {
    // Uncomment to see continuous mouse position updates
    // std::cout << "Mouse at: (" << event.position.x << ", " << event.position.y << ")" << std::endl;
}

void GameEngine::handleEvent(const sf::Event::Resized& event) {
    std::cout << "Window resized to: " << event.size.x << "x" << event.size.y << std::endl;
}

void GameEngine::drawTestGrid() {
    const float gridSpacing = 50.0f;
    auto windowSize = window.getSize();
    
    sf::Color gridColor(50, 50, 50);
    
    // Vertical lines
    for (float x = 0; x <= windowSize.x; x += gridSpacing) {
        sf::RectangleShape line({1.0f, static_cast<float>(windowSize.y)});
        line.setPosition({x, 0.0f});
        line.setFillColor(gridColor);
        window.draw(line);
    }
    
    // Horizontal lines
    for (float y = 0; y <= windowSize.y; y += gridSpacing) {
        sf::RectangleShape line({static_cast<float>(windowSize.x), 1.0f});
        line.setPosition({0.0f, y});
        line.setFillColor(gridColor);
        window.draw(line);
    }
}