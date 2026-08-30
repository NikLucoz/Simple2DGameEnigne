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
Vector2<T> Vector2<T>::normalized() const
{
    T mag = this->magnitude();
    if (mag > 0)
        return Vector2<T>(this->x / mag, this->y / mag);
    return *this;
}

template <class T>
T Vector2<T>::angle() const
{
    return atan2(this->y, this->x);
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

template <typename T>
float Vector2<T>::distanceToSquared(const Vector2<T> other) const
{
    float dx = x - other.x;
    float dy = y - other.y;
    return dx * dx + dy * dy;
}

template <class T>
Vector2<T> Vector2<T>::reflectionVector(const Vector2<T>& normal)
{
    T scalarProduct = normal.dot(*this);
    Vector2<T> dividendVector = normal * (2 * scalarProduct);
    T divisor = normal.dot(normal);
    Vector2<T> subtrahendVector = dividendVector * (1 / divisor);
    
    return *this - subtrahendVector;
}

template <class T>
std::string Vector2<T>::toString() const
{
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

template class Vector2<float>;
template class Vector2<int>;
template class Vector2<double>;