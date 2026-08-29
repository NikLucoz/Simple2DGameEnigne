#include "EntityManager.h"

#include <algorithm>

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

    std::vector<std::shared_ptr<Entity>> toRemove;
    // remove entities listed for destruction
    for (auto& e : m_entities)
    {
        if (e->is_marked_for_destruction() == false) continue;
        toRemove.push_back(e);
    }
    
    for (auto& e : toRemove)
    {
        auto it = std::find(m_entities.begin(), m_entities.end(), e);
        m_entities.erase(it);
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