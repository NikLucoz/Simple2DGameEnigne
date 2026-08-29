#pragma once
#include <SFML/Window/Window.hpp>

#include "engine/entities/EntityManager.h"
#include "engine/systems/RenderSystem.h"

class GameManager
{
	sf::Window window_;
	EntityManager entityManager_;
	bool bPaused_;
	bool bRunning_;
	
	RenderSystem sRenderSystem_;
	
	void init();
public:
	GameManager() = default;
	void update();
};
