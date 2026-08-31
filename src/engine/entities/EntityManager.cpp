#include "EntityManager.h"

#include <algorithm>

EntityManager& EntityManager::getInstance()
{
    static EntityManager instance;
    return instance;
}

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
        if (it != entities_.end()) {
            entities_.erase(it);
        }
    
        auto& taggedEntities = entitiesMap_[e->getTag()];
        auto it2 = std::find(taggedEntities.begin(), taggedEntities.end(), e);
        if (it2 != taggedEntities.end()) {
            taggedEntities.erase(it2);
        }
    
        if (entitiesMap_[e->getTag()].empty()) {
            entitiesMap_.erase(e->getTag());
        }
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