#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(const std::string& tag, const std::string& sceneName, size_t id, const std::string& name)
{
    name_ = name;
    tag_ = tag;
    id_ = id;
    sceneName_ = sceneName;
}


size_t Entity::getId() const
{
    return id_;
}

void Entity::destroy()
{
    bIsMarkedForDestruction_ = true;
}

const std::string& Entity::getTag() const
{
    return tag_;
}

const std::string &Entity::getSceneName() const
{
    return sceneName_;
}

const std::string &Entity::getName() const
{
    return name_;
}

bool Entity::isMarkedForDestruction() const
{
    return bIsMarkedForDestruction_;
}
