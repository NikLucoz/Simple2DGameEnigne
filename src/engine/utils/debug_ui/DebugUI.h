#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include "engine/entities/EntityManager.h"
class DebugUI
{
private:
	// initialize IMGUI and create a clock used for its internal timing
	sf::RenderWindow* Window;
	
public:
	DebugUI();

	bool IsLifeSpanActive{ true };
	bool IsSpawnerActive{ true };
	bool IsMovementActive{ true };
	bool IsSpecialShootActive{ true };
	bool IsCollisionActive{ true };
	bool IsRenderActive{ true };
	bool IsGuiActive{ true };

	int SpawnInterval;
	bool ManuelSpawnFlag{ false };

	void Init(sf::RenderWindow* window, uint16_t initialSpawnInterval);
	void Update(sf::Clock& deltaClock, EntityMap& EntitiesMap);
	void Render();
	void ProcessEvent(sf::Event& event);
	int GetSpawnInterval();
	bool GetManuelSpawnFlag();
	bool GetAnyItemHovered();
};
