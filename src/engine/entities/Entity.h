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
    CCircleShape,
    CPolygonShape,
    CRectangleShape
>;

class Entity
{
private:
    ComponentTuple m_components;
    bool m_isMarkedForDestruction = false;
    std::string m_tag = "default";
    size_t m_id = 0;

public:
    Entity();
    Entity(const std::string& tag, size_t id);
    
    template <typename T>
    T& get()
    {
        return std::get<T>(m_components);
    }

    template <typename T>
    bool has()
    {
        return get<T>().exists;
    }

    template <typename T, typename... TArgs>
    T& add(TArgs&&... mArgs)
    {
        auto& component = get<T>();
        component = T(std::forward<TArgs>(mArgs)...);
        component.exists = true;
        return component;
    }

    template <typename T>
    void remove()
    {
        get<T>() = T();
        get<T>().exists = false;
    }

    size_t id() const;
    void destroy();
    const std::string& tag() const;
    bool is_marked_for_destruction() const;
};

