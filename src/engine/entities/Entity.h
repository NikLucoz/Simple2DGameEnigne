#pragma once
#include <memory>
#include <string>
#include <tuple>

#include "engine/components/CInput.h"
#include "engine/components/CShape.h"
#include "engine/components/CSprite.h"
#include "engine/components/CTransform.h"

using ComponentTuple = std::tuple<
    CTransform,
    CSprite,
    CShape,
    CInput
>;

class Entity
{
private:
    ComponentTuple components_;
    bool bIsMarkedForDestruction_ = false;
    std::string tag_ = "default";
    size_t id_ = 0;

protected:
    Entity();
    Entity(const std::string& tag, size_t id);

public:
    
    template <typename T>
    T& getComponent()
    {
        return std::get<T>(components_);
    }

    template <typename T>
    bool hasComponent()
    {
        return getComponent<T>().exists;
    }

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        auto& component = getComponent<T>();
        component = T(std::forward<TArgs>(mArgs)...);
        component.exists = true;
        return component;
    }

    template <typename T>
    void removeComponent()
    {
        getComponent<T>() = T();
        getComponent<T>().exists = false;
    }

    size_t getId() const;
    void destroy();
    const std::string& getTag() const;
    bool isMarkedForDestruction() const;
    
    // with this only the EntityManager can create Entities since the constructors are private
    friend class EntityManager;
};

