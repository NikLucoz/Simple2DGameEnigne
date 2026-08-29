#pragma once
#include <SFML/Graphics/Color.hpp>
#include <variant>
#include "engine/components/Component.h"

class CCircleShape : public Component
{
public:
    float radius;
    sf::Color fillColor;
    sf::Color OutlineColor;
    uint16_t OutlineThickness;
    CCircleShape() = default;
    CCircleShape(float radius, sf::Color fillColor, sf::Color OutlineColor, uint16_t OutlineThickness);
};

class CRectangleShape : public Component
{
public:
    float width, height;
    sf::Color fillColor;
    sf::Color OutlineColor;
    uint16_t OutlineThickness;
    CRectangleShape() = default;
    CRectangleShape(float width, float height, sf::Color FillColor, sf::Color OutlineColor, uint16_t OutlineThickness);
};

class CPolygonShape : public Component
{
public:
    uint32_t pointCount;
    float radius;
    sf::Color fillColor;
    sf::Color OutlineColor;
    uint16_t OutlineThickness;
    CPolygonShape() = default;
    CPolygonShape(uint32_t pointCount, float radius, sf::Color FillColor, sf::Color OutlineColor, uint16_t OutlineThickness);
};