#pragma once
#include <SFML/Graphics/Color.hpp>
#include <variant>
#include "engine/components/Component.h"

class CShape : public Component
{
public:
    float radius_;
    int8_t point_count_;
    sf::Color fillColor_;
    sf::Color outlineColor_;
    uint16_t outlineThickness_;
    CShape() = default;
    CShape(float radius, int8_t point_count, sf::Color fillColor, sf::Color OutlineColor, uint16_t OutlineThickness);
};
