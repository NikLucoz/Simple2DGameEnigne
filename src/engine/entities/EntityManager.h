#pragma once
#include <map>
#include <memory>
#include <vector>

#include "Entity.h"

using EntityVec = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<std::string, EntityVec>;
class EntityManager
{
    EntityVec m_entities;
    EntityMap m_entitiesMap;
    EntityVec m_toAdd;
    size_t m_totalEntities = 0;
public: 
    EntityManager();
    void update();
    std::shared_ptr<Entity> addEntity(const std::string& tag);
    EntityVec& getEntities();
    EntityVec& getEntities(const std::string& tag);
};
