#pragma once
#include "Scene.h"

class Action;

class MainMenuScene : public Scene
{ 
    public:
    MainMenuScene(GameEngine* gameEngine);
    void update(float dt) override;
    void sRender(float dt) override;
    void sDebug() override;
    void sDoAction(const Action& action) override;
};