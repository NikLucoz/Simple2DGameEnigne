#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "engine/entities/Entity.h"

using EntityVec = std::vector<std::shared_ptr<Entity>>;

class DebugUI {
private:
	sf::RenderWindow* Window = nullptr;

public:
	DebugUI();
	void Init(sf::RenderWindow& window);
	void Update(sf::Clock& deltaClock);
	void Render();
	void ProcessEvent(sf::Event& event);
	bool GetAnyItemHovered();
};