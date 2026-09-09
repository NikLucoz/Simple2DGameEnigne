#pragma once

#include "engine/entities/Entity.h"
#include "engine/utils/math/Vector2.h"          

Vector2<int> getOverlap(Entity* entity1, Entity* entity2);
bool IsColliding(Entity* entity1, Entity* entity2);
bool IsIntersect(Entity* entity1, Entity* entity2);
bool IsInside(Entity* entity, const Vec2f& pointPos);