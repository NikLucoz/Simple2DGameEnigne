#include "MainMenuScene.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "engine/actions/Action.h"
#include "ScenePlay.h"

MainMenuScene::MainMenuScene(GameEngine* gameEngine) : Scene(gameEngine) {
    registerAction(InputDevice::Keyboard, static_cast<int>(sf::Keyboard::Key::Enter), "UI_Enter");
    registerAction(InputDevice::Keyboard, static_cast<int>(sf::Keyboard::Key::Escape), "UI_Escape");
    registerAction(InputDevice::Keyboard, static_cast<int>(sf::Keyboard::Key::Up), "UI_Up");
    registerAction(InputDevice::Keyboard, static_cast<int>(sf::Keyboard::Key::Down), "UI_Down");
}

void MainMenuScene::init()
{
}

void MainMenuScene::destroy()
{
}

void MainMenuScene::update(float dt)
{
}

void MainMenuScene::sRender(float dt)
{
}

void MainMenuScene::sDebug()
{
}

void MainMenuScene::sDoAction(const Action &action)
{
    if (action.name() == "UI_Enter") {
        gameEngine_->changeScene("gameplay_scene");
    }
}
