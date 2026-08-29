#pragma once
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
    T normalize();
    T angle() const;
    sf::Vector2<T> toSFVector2() const;
};

using Vec2f = Vector2<float>;
