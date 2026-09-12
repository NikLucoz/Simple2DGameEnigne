#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Entity.h"


using EntityVec = std::vector<std::shared_ptr<Entity>>;
using EntityTagMap = std::map<std::string, EntityVec>;
using EntitySceneMap = std::map<std::string, EntityVec>;
class EntityManager
{
private:
    EntityVec entities_;
    EntityTagMap entitiesMap_;
    EntitySceneMap entitiesSceneMap_;
    EntityVec toAdd_;
    size_t totalEntities_ = 0;
    EntityManager() = default;
public:
    static EntityManager& getInstance();
    void update();
    std::shared_ptr<Entity> addEntity(const std::string& tag, const std::string& sceneName = "", const std::string& entityName = "entity");

    template<typename T>
    std::shared_ptr<T> addEntity(const std::string& tag, const std::string& sceneName = "", const std::string& entityName = "entity");
    
    EntityVec& getEntities();
    EntityVec& getEntities(const std::string& tag);
    EntityVec getEntities(const std::vector<std::string>& tags);
    EntityVec& getEntitiesInScene(const std::string& sceneName);
};

template<typename T>
std::shared_ptr<T> EntityManager::addEntity(const std::string& tag, const std::string& sceneName, const std::string& entityName)
{
    auto entity = std::make_shared<T>(tag, sceneName, totalEntities_++, entityName);
    toAdd_.push_back(entity);
    return entity;
}
