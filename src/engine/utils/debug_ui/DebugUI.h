#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include <memory>
#include "engine/entities/Entity.h"

class Assets;

using EntityVec = std::vector<std::shared_ptr<Entity>>;

struct DebugRuntimeInfo
{
	float framesPerSecond = 0.0f;
	sf::Vector2u windowSize;
	std::string currentScene;
	std::vector<std::string> loadedScenes;
	std::vector<std::string> textures;
	std::vector<std::string> animations;
	std::vector<std::string> sounds;
	std::vector<std::string> fonts;
};

struct DebugOptions
{
	bool showDebugUI = false;
	bool showEntityIds = false;
	bool showCollisionGeometry = false;

	struct
	{
		bool render = true;
		bool movement = true;
		bool collision = true;
		bool lifespan = true;
		bool animation = true;
		bool enemySpawner = false;
	} systems;
};

class DebugUI {
private:
	sf::RenderWindow* Window = nullptr;
	bool initialized_ = false;
	bool frameStarted_ = false;
	bool visible_ = false;
	DebugOptions options_;

public:
	DebugUI();
	void Init(sf::RenderWindow& window, const Assets& assets);
	void Update(sf::Time deltaTime, const DebugRuntimeInfo& runtimeInfo,
		const std::function<void()>& drawSceneContent,
		const std::function<void(const std::string&)>& changeScene);
	void Render();
	void ProcessEvent(sf::Event& event);
	void SetVisible(bool visible);
	bool IsVisible() const;
	bool WantsKeyboardInput() const;
	bool WantsMouseInput() const;
	bool GetAnyItemHovered();
	DebugOptions& GetOptions();
	const DebugOptions& GetOptions() const;
};