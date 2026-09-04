#pragma once
#include <type_traits>
#include <SFML/System/Clock.hpp>

class EPlayer;
class EntityManager;

class MovementSystem
{
    MovementSystem() = default;
public:
    bool bIsActive_ = true;
    static MovementSystem& getInstance();
    void update(EPlayer* get, float delta_time, sf::Clock clock);
};
