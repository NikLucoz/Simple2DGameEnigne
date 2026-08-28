#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(const std::string& tag, size_t id)
{
    m_tag = tag;
    m_id = id;
}


size_t Entity::id() const
{
    return m_id;
}

void Entity::destroy()
{
    m_isMarkedForDestruction = true;
}

const std::string& Entity::tag() const
{
    return m_tag;
}

bool Entity::is_marked_for_destruction() const
{
    return m_isMarkedForDestruction;
}
