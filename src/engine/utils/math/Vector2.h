#pragma once
#include <SFML/System/Vector2.hpp>

class Vector2
{
public:
    float x = 0, y = 0;
    Vector2();
    Vector2(float x, float y);
    bool operator == (const Vector2& other) const;
    Vector2 operator + (const Vector2& other) const;
    Vector2 operator - (const Vector2& other) const;
    Vector2 operator * (const Vector2& other) const;
    Vector2 operator * (float f) const;
    float magnitude() const;
    float dot(const Vector2& other) const;
    float normalize();
    float angle() const;
    sf::Vector2<float> toSFVector2() const;
};
