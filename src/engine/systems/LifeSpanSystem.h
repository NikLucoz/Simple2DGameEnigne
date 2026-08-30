#pragma once

class EntityManager;

class LifeSpanSystem
{
public:
  void update(EntityManager entity_manager, double delta_time);  
};
