#include "CShape.h"

CCircleShape::CCircleShape(float radius, sf::Color fillColor, sf::Color OutlineColor, uint16_t OutlineThickness)
    : radius(radius), fillColor(fillColor), OutlineColor(OutlineColor), OutlineThickness(OutlineThickness)
{
    exists = true;
}

CRectangleShape::CRectangleShape(float width, float height, sf::Color FillColor, sf::Color OutlineColor, uint16_t OutlineThickness)
    : width(width), height(height), fillColor(FillColor), OutlineColor(OutlineColor), OutlineThickness(OutlineThickness)
{
    exists = true;
}

CPolygonShape::CPolygonShape(uint32_t pointCount, float radius, sf::Color FillColor, sf::Color OutlineColor, uint16_t OutlineThickness)
    : pointCount(pointCount), radius(radius), fillColor(FillColor), OutlineColor(OutlineColor), OutlineThickness(OutlineThickness)
{
    exists = true;
}