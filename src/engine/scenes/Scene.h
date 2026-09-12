#pragma once
#include <map>
#include <string>

class Action;
class Entity;
class GameEngine;

enum class InputDevice
{
    Keyboard,
    MouseButton
};

struct InputBinding
{
    InputDevice device;
    int code;

    bool operator<(const InputBinding& other) const
    {
        if (device != other.device)
            return device < other.device;

        return code < other.code;
    }
};
using ActionMap = std::map<InputBinding, std::string>;

class Scene
{
    int currentFrame_ = 0;
    ActionMap actionMap_;
    bool bIsPaused_ = false;
    bool bHasEnded_ = false;
protected:
    GameEngine* gameEngine_ = nullptr;
public:
    bool bShouldShowDebug_ = true;

    explicit Scene(GameEngine* gameEngine);
    virtual ~Scene() = default;
    virtual void update(float dt) = 0;
    virtual void sRender(float dt) = 0;
    virtual void sDebug() = 0;
    virtual void sDoAction(const Action& action) = 0;
    void simulate(int);
    void doAction(const Action& action);
    void registerAction(InputDevice device, int code, const std::string& actionName);
    ActionMap& getActionMap();
};