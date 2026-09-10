#include "Scene.h"
#include "engine/GameEngine.h"

Scene::Scene(GameEngine* gameEngine)
    : gameEngine_(gameEngine)
{
}

void Scene::doAction(const Action &action)
{
    // TODO: Extra bookkeeping for actions if needed before forwarding to the specific scene
    sDoAction(action);
}

void Scene::registerAction(InputDevice device, int code, const std::string& actionName)
{
    actionMap_[{ device, code }] = actionName;
}

ActionMap& Scene::getActionMap()
{
    return actionMap_;
}
