#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>


template <class T>
class Vector2
{
public:
    T x = 0, y = 0;
    
    Vector2();
    Vector2(T x, T y);
    
    bool operator==(const Vector2<T>& other) const;
    Vector2<T> operator+(const Vector2<T>& other) const;
    Vector2<T> operator-(const Vector2<T>& other) const;
    Vector2<T> operator*(const Vector2<T>& other) const;
    Vector2<T> operator*(float f) const;
    
    T magnitude() const;
    T dot(const Vector2<T>& other) const;
    Vector2<T> normalized() const;
    T angle() const;
    sf::Vector2<T> toSFVector2() const;
    float distanceTo(const Vector2<T> vector2) const;
    float distanceToSquared(Vector2<T> other) const;
    Vector2<T> reflectionVector(const Vector2<T>& normal);
    std::string toString() const;

};

using Vec2f = Vector2<float>;
