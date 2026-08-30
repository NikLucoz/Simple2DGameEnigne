#include "Vector2.h"
#include <cmath>

template <class T>
Vector2<T>::Vector2()
{
    this->x = 0;
    this->y = 0;
}

template <class T>
Vector2<T>::Vector2(T x, T y)
{
    this->x = x;
    this->y = y;
}

template <class T>
bool Vector2<T>::operator==(const Vector2<T>& other) const
{
    return this->x == other.x && this->y == other.y;
}

template <class T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& other) const
{
    return Vector2<T>(this->x + other.x, this->y + other.y);
}

template <class T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& other) const
{
    return Vector2<T>(this->x - other.x, this->y - other.y);
}

template <class T>
Vector2<T> Vector2<T>::operator*(const Vector2<T>& other) const
{
    return Vector2<T>(this->x * other.x, this->y * other.y);
}

template <class T>
Vector2<T> Vector2<T>::operator*(float f) const
{
    return Vector2<T>(this->x * f, this->y * f);
}

template <class T>
T Vector2<T>::magnitude() const
{
    return sqrt(x * x + y * y);
}

template <class T>
T Vector2<T>::dot(const Vector2<T>& other) const
{
    return this->x * other.x + this->y * other.y;
}

template <class T>
T Vector2<T>::normalize()
{
    T mag = this->magnitude();
    if (mag > 0)
    {
        this->x /= mag;
        this->y /= mag;
    }
    return mag;
}

template <class T>
T Vector2<T>::angle() const
{
    return atan2(this->y, this->x);  // Fixed: was atan2(x, y)
}

template <class T>
sf::Vector2<T> Vector2<T>::toSFVector2() const
{
    return sf::Vector2<T>(this->x, this->y);
}

template <typename T>
float Vector2<T>::distanceTo(const Vector2<T> other) const
{
    float dx = x - other.x;
    float dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

// Explicit instantiations (add these at the end)
template class Vector2<float>;
template class Vector2<int>;
template class Vector2<double>;