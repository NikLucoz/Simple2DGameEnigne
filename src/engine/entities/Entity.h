#pragma once
#include <memory>
#include <string>
#include <tuple>

#include "engine/components/CShape.h"
#include "engine/components/CSprite.h"
#include "engine/components/CTransform.h"

using ComponentTuple = std::tuple<
    CTransform,
    CSprite,
    CShape
>;

class Entity
{
private:
    ComponentTuple components_;
    bool bIsMarkedForDestruction_ = false;
    std::string tag_ = "default";
    size_t id_ = 0;

    Entity();
    Entity(const std::string& tag, size_t id);
public:
    
    template <typename T>
    T& get()
    {
        return std::get<T>(components_);
    }

    template <typename T>
    bool has()
    {
        return get<T>().active;
    }

    template <typename T, typename... TArgs>
    T& add(TArgs&&... mArgs)
    {
        auto& component = get<T>();
        component = T(std::forward<TArgs>(mArgs)...);
        component.active = true;
        return component;
    }

    template <typename T>
    void remove()
    {
        get<T>() = T();
        get<T>().active = false;
    }

    size_t getId() const;
    void destroy();
    const std::string& getTag() const;
    bool isMarkedForDestruction() const;
    
    // with this only the EntityManager can create Entities since the constructors are private
    friend class EntityManager;
};

