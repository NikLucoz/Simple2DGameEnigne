#include "EntityManager.h"

EntityManager::EntityManager() = default;

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    auto e = std::make_shared<Entity>(tag, m_totalEntities++);
    m_toAdd.push_back(e);
    return e;
}

void EntityManager::update()
{
    // add pending entities
    for (auto& e : m_toAdd)
    {
        m_entities.push_back(e);
        m_entitiesMap[e->tag()].push_back(e);
    }

    // remove entities listed for destruction
    for (auto& e : m_entities)
    {
        if (e->is_marked_for_destruction() == false) continue;
        // find a way to solve iterator invalidation
    }
    
    m_toAdd.clear();
}

EntityVec& EntityManager::getEntities()
{
    return m_entities;
}

EntityVec& EntityManager::getEntities(const std::string& tag)
{
    return m_entitiesMap[tag];
}