#pragma once
#include <map>
#include <memory>
#include <vector>

#include "Entity.h"


using EntityVec = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<std::string, EntityVec>;
class EntityManager
{
private:
    EntityVec entities_;
    EntityMap entitiesMap_;
    EntityVec toAdd_;
    size_t totalEntities_ = 0;
    EntityManager() = default;
public:
    static EntityManager& getInstance();
    void update();
    std::shared_ptr<Entity> addEntity(const std::string& tag);

    template<typename T>
    std::shared_ptr<T> addEntity(const std::string& tag)
    {
        auto e = std::make_shared<T>(tag, totalEntities_++);
        toAdd_.push_back(std::static_pointer_cast<Entity>(e));
        return e;
    }
    
    EntityVec& getEntities();
    EntityVec& getEntities(const std::string& tag);
};
