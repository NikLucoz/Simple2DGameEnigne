#include "Vector2.h"
#include <cmath>

Vector2::Vector2()
{
    this->x = 0.0f;
    this->y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

bool Vector2::operator==(const Vector2& other) const
{
    return this->x == other.x && this->y == other.y;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2(this->x + other.x, this->y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return Vector2(this->x - other.x, this->y - other.y);
}

Vector2 Vector2::operator*(const Vector2& other) const
{
    // Element-wise multiplication (Hadamard product)
    return Vector2(this->x * other.x, this->y * other.y);
}

Vector2 Vector2::operator*(float f) const
{
    return Vector2(this->x * f, this->y * f);
}

float Vector2::magnitude() const
{
    return sqrt(x * x + y * y);
}

float Vector2::dot(const Vector2& other) const
{
    return this->x * other.x + this->y * other.y;
}

float Vector2::normalize()
{
    float mag = this->magnitude();
    if (mag > 0.0f)
    {
        this->x /= mag;
        this->y /= mag;
    }
    return mag;
}

float Vector2::angle() const
{
    return atan2(this->x, this->y);
}

sf::Vector2<float> Vector2::toSFVector2() const
{
    return sf::Vector2<float>(this->x, this->y);
}
