#include "agarios/Vector2d.h"
#include <iostream>
#include <math.h>

Vector2d::Vector2d()
{
    this->x = 0;
    this->y = 0;
}

Vector2d::Vector2d(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2d::Vector2d(Vector2d& v)
{
    this->x = v.x;
    this->y = v.y;
}

Vector2d& Vector2d::set(Vector2d &v)
{
    this->x = v.x;
    this->y = v.y;
    return *this;
}

Vector2d& Vector2d::set(float x, float y)
{
    this->x = x;
    this->y = y;
    return *this;
}

Vector2d& Vector2d::add(Vector2d &v)
{
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vector2d& Vector2d::subtract(Vector2d &v)
{
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

Vector2d& Vector2d::add(float s)
{
    this->x += s;
    this->y += s;
    return *this;
}

Vector2d& Vector2d::subtract(float s)
{
    this->x -= s;
    this->y -= s;
    return *this;
}

Vector2d& Vector2d::multiply(float s)
{
    this->x *= s;
    this->y *= s;
    return *this;
}

Vector2d& Vector2d::divide(float d)
{
    this->x /= d;
    this->y /= d;
    return *this;
}

Vector2d& Vector2d::normalize()
{
    float length = this->length();
    if (length == 0) this->x = 1;
    else this->divide(length);
    return *this;
}

float Vector2d::length()
{
    return sqrt(this->x * this->x + this->y * this->y);
}

Vector2d& Vector2d::setLength(float l)
{
    this->normalize();
    this->multiply(l);
    return *this;
}

float Vector2d::getAngle()
{
    return atan2(this->y, this->x);
}

float Vector2d::getAngleDeg()
{
    return atan2(this->y, this->x) * 180.0/M_PI;
}

Vector2d& Vector2d::setAngle(float a)
{
    float length = this->length();
    this->x = cos(a) * length;
    this->y = sin(a) * length;
    return *this;
}

Vector2d& Vector2d::setAngleDeg(float a)
{
    this->setAngle(a * (M_PI/180.0));
    return *this;
}

Vector2d& Vector2d::rotateBy(float l)
{
    float angle = this->getAngle();
    float length = this->length();
    this->x = cos(l + angle) * length;
    this->y = sin(l + angle) * length;
    return *this;
}

float Vector2d::dot(Vector2d &v)
{
    return this->x * v.x + this->y * v.y;
}

float Vector2d::cross(Vector2d &v)
{
    return (this->x * v.y) - (this->y * v.x);
}

float Vector2d::distance(Vector2d v)
{
    Vector2d distanceVector = v - *this;
    return distanceVector.length();
}

Vector2d& Vector2d::pointTo(Vector2d &v)
{
    Vector2d vectorToTarget = v - *this;
    this->setAngle(vectorToTarget.getAngle());
    return *this;
}

//OPERATORS

Vector2d Vector2d::operator+(const Vector2d &v) const
{
    return Vector2d(this->x + v.x, this->y + v.y);
}

Vector2d Vector2d::operator-(const Vector2d &v) const
{
    return Vector2d(this->x - v.x, this->y - v.y);
}

Vector2d Vector2d::operator*(const float s) const
{
    return Vector2d(this->x * s, this->y * s);
}

//dot product
float Vector2d::operator*(const Vector2d &v) const
{
    return (this->x * v.x + this->y * v.y);
}

//cross product
float Vector2d::operator^(const Vector2d &v) const
{
    return (this->x * v.y) - (this->y * v.x);
}

Vector2d Vector2d::operator/(const float s) const
{
    return Vector2d(this->x / s, this->y / s);
}

Vector2d Vector2d::operator/(const Vector2d &v) const
{
    return Vector2d(this->x / v.x, this->y / v.y);
}

bool Vector2d::operator==(const Vector2d &v) const
{
    return (this->x == v.x && this->y == v.y);
}

void Vector2d::operator=(const Vector2d &v)
{
    this->x = v.x;
    this->y = v.x;
}

void Vector2d::operator+=(const Vector2d &v)
{
    this->x += v.x;
    this->y += v.y;
}

void Vector2d::operator-=(const Vector2d &v)
{
    this->x -= v.x;
    this->y -= v.y;
}

void Vector2d::operator+=(const float s)
{
    this->x += s;
    this->y += s;
}

void Vector2d::operator-=(const float s)
{
    this->x -= s;
    this->y -= s;
}

void Vector2d::operator*=(const float s)
{
    this->x *= s;
    this->y *= s;
}

void Vector2d::operator/=(const float s)
{
    this->x /= s;
    this->y /= s;
}

float Vector2d::operator[](int i)
{
    if (i == 0) return this->x;
    else return this->y;
}