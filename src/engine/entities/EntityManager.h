#pragma once
#include <map>
#include <memory>
#include <vector>

#include "Entity.h"

using EntityVec = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<std::string, EntityVec>;
class EntityManager
{
    EntityVec entities_;
    EntityMap entitiesMap_;
    EntityVec toAdd_;
    size_t totalEntities_ = 0;
public: 
    EntityManager();
    void update();
    std::shared_ptr<Entity> addEntity(const std::string& tag);
    EntityVec& getEntities();
    EntityVec& getEntities(const std::string& tag);
};
