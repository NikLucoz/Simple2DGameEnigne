#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(const std::string& tag, size_t id)
{
    tag_ = tag;
    id_ = id;
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

bool Entity::isMarkedForDestruction() const
{
    return bIsMarkedForDestruction_;
}
