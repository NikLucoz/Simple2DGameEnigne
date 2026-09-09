#pragma once
#include <map>
#include <string>

class Action;
class Entity;
class GameEngine;

class Scene
{
    int currentFrame_ = 0;
    std::map<int, std::string> actionMap_;
    bool bIsPaused_ = false;
    bool bHasEnded_ = false;
protected:
    GameEngine* gameEngine_ = nullptr;
public:
    explicit Scene(GameEngine* gameEngine);
    bool bShouldShowDebug_ = false;
    virtual ~Scene() = default;
    virtual void update(float dt) = 0;
    virtual void sRender(float dt) = 0;
    virtual void sDebug() = 0;
    virtual void sDoAction(const Action& action) = 0;
    void simulate(int);
    
    //void doAction(action);
    //void registerAction(action);
};
