#pragma once
#include <engine/utils/math/Vector2.h>
#include <engine/entities/Entity.h>
#include <engine/entities/EntityManager.h>
#include <limits>

//https://www.redblobgames.com/articles/visibility/

struct Intersect {
    bool result;
    Vec2f position;
};

struct RayHit {
    bool result;
    Entity* hit;
    Vec2f position;
};


class Raycast2D {
    static Intersect lineIntersect(Vec2f a, Vec2f b, Vec2f c, Vec2f d) {
        Vec2f r = (b - a);
        Vec2f s = (d - c);
        float rxs = r.crossProduct(s);
        if (rxs == 0.0f) return {false, Vec2f(0.0f, 0.0f)};

        Vec2f cma = c - a;
        float t  = (cma.crossProduct(s)) / rxs;
        float u = (cma.crossProduct(r)) / rxs;
        if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
            return {true, Vec2f(a.x + t*r.x, a.y + t*r.y)};
        }

        return { false, Vec2f(0, 0)};
    }
    
    public:
    static RayHit castRay(Vec2f origin, Vec2f direction, float length, Entity* ignoredEntity = nullptr) {
        auto& entities = EntityManager::getInstance().getEntities();
        Vec2f rayEndPoint = origin + direction.normalized() * length;
        float closestDistanceSquared = std::numeric_limits<float>::max();
        Entity* closestEntity = nullptr;
        Vec2f closestPosition = Vec2f(0.0f, 0.0f);

        for (std::shared_ptr<Entity>& ePtr : entities) {
            Entity& e = *ePtr;

            if (&e == ignoredEntity) continue;

            if (!e.hasComponent<CBoundingBox>() || !e.hasComponent<CTransform>()) continue;
            CTransform& eTransform = e.getComponent<CTransform>();
            CBoundingBox& eBoundingBox = e.getComponent<CBoundingBox>();
            
            Vec2f halfSize = Vec2f(eBoundingBox.size.x / 2.0f, eBoundingBox.size.y / 2.0f);

            Vec2f topLeft = eTransform.position - halfSize;
            Vec2f topRight = Vec2f(eTransform.position.x + halfSize.x, eTransform.position.y - halfSize.y);
            Vec2f bottomRight = eTransform.position + halfSize;
            Vec2f bottomLeft = Vec2f(eTransform.position.x - halfSize.x, eTransform.position.y + halfSize.y);

            Intersect intersect1 = lineIntersect(origin, rayEndPoint, topLeft, topRight);
            Intersect intersect2 = lineIntersect(origin, rayEndPoint, topRight, bottomRight);
            Intersect intersect3 = lineIntersect(origin, rayEndPoint, bottomRight, bottomLeft);
            Intersect intersect4 = lineIntersect(origin, rayEndPoint, bottomLeft, topLeft);

            const Intersect intersects[] = {intersect1, intersect2, intersect3, intersect4};
            for (const Intersect& intersect : intersects) {
                if (!intersect.result) continue;

                float distanceSquared = origin.distanceToSquared(intersect.position);
                if (distanceSquared < closestDistanceSquared) {
                    closestDistanceSquared = distanceSquared;
                    closestEntity = ePtr.get();
                    closestPosition = intersect.position;
                }
            }

        }

        return {closestEntity != nullptr, closestEntity, closestPosition};
    }
};