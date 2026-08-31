#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include <SFML/Graphics.hpp>
#include "entities/EntityManager.h"
#include "entities/EPlayer.h"
#include "engine/utils/debug_ui/DebugUI.h"

class GameEngine {
private:
    sf::RenderWindow window_;
    sf::Clock clock_;
    bool bIsRunning_;
    DebugUI debugUI_;
    std::shared_ptr<EPlayer> player_ = nullptr;
public:
    GameEngine(unsigned int width = 800, unsigned int height = 600, const std::string& title = "Game Engine");
    ~GameEngine();

    bool isOpen() const;
    void handleEvents();
    void update(float deltaTime);
    void render(float deltaTime);
    void run();

private:
    // Event handlers
    void handleEvent(const sf::Event::Closed&);
    void handleEvent(const sf::Event::KeyPressed& event);
    void handleEvent(const sf::Event::KeyReleased& event);
    void handleEvent(const sf::Event::MouseButtonPressed& event);
    void handleEvent(const sf::Event::MouseMoved& event);
    void handleEvent(const sf::Event::Resized& event);

    // Catch-all for other event types
    template<typename T>
    void handleEvent(const T&) {
        // Other events we don't handle
    }

    void drawTestGrid();
};

#endif