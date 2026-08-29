#include "EntityManager.h"

#include <algorithm>

EntityManager::EntityManager() = default;

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    auto e = std::shared_ptr<Entity>(new Entity(tag, totalEntities_++));
    toAdd_.push_back(e);
    return e;
}

void EntityManager::update()
{
    for (auto& e : toAdd_)
    {
        entities_.push_back(e);
        entitiesMap_[e->getTag()].push_back(e);
    }

    std::vector<std::shared_ptr<Entity>> toRemove;
    for (auto& e : entities_)
    {
        if (e->isMarkedForDestruction() == false) continue;
        toRemove.push_back(e);
    }
    
    for (auto& e : toRemove)
    {
        auto it = std::find(entities_.begin(), entities_.end(), e);
        entities_.erase(it);
    }
    
    toAdd_.clear();
}

EntityVec& EntityManager::getEntities()
{
    return entities_;
}

EntityVec& EntityManager::getEntities(const std::string& tag)
{
    return entitiesMap_[tag];
}