#include "LifeSpanSystem.h"

#include <iostream>

#include "engine/entities/EntityManager.h"

void LifeSpanSystem::update(EntityManager entityManager, double deltaTime)
{
    auto& entities = entityManager.getEntities();
    
    for (auto& entity : entities)
    {
        if (!entity->hasComponent<CLifespan>()) continue;
        CLifespan& cLifespan = entity->getComponent<CLifespan>();
        cLifespan.remainingSeconds_ -= deltaTime;
        if (cLifespan.remainingSeconds_ <= 0) {
            cLifespan.remainingSeconds_ = 0;
        }

        if (entity->hasComponent<CShape>()) {
            CShape& cShape = entity->getComponent<CShape>();
            uint8_t alpha = (cLifespan.remainingSeconds_ / cLifespan.lifespanSeconds_) * 255;
            cShape.fillColor_.a = alpha;
            cShape.outlineColor_.a = alpha;
            cShape.getShape()->setFillColor(cShape.fillColor_);
            cShape.getShape()->setOutlineColor(cShape.outlineColor_);
        }

        if (cLifespan.remainingSeconds_ <= 0)
        {
            entity->destroy();
        }
    }
}
