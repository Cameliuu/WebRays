// Vector3.cpp : Defines the functions for the static library.


#include "Vector3.h"
#include <cmath>

// CONSTRUCTORS
Vector3::Vector3() : x(0.0), y(0.0), z(0.0) {}
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

// DESTRUCTORS
Vector3::~Vector3() {}

// GETTERS
float Vector3::GetX() const { return x; }
float Vector3::GetY() const { return y; }
float Vector3::GetZ() const { return z; }

// SETTERS
void Vector3::SetX(float x) { this->x = x; }
void Vector3::SetY(float y) { this->y = y; }
void Vector3::SetZ(float z) { this->z = z; }

// METHODS
float Vector3::Magnitude() const { return sqrt(x * x + y * y + z * z); }

float Vector3::Dot(const Vector3& Other) const { return (this->x * Other.x) + (this->y * Other.y) + (this->z * Other.z); }

Vector3 Vector3::Normalize() const
{
    float magnitude = Magnitude();
    if (magnitude != 0.0f)
    {
        return Vector3(x / magnitude, y / magnitude, z / magnitude);
    }
    else
    {
        return Vector3();
    }
}

// OPERATOR OVERLOADS
Vector3 Vector3::operator+(const Vector3& Other) const { return Vector3(this->x + Other.x, this->y + Other.y, this->z + Other.z); }
Vector3 Vector3::operator-(const Vector3& Other) const { return Vector3(this->x - Other.x, this->y - Other.y, this->z - Other.z); }
Vector3 Vector3::operator*(float value) const { return {this->x * value, this->y * value, this->z * value}; }
bool Vector3::operator==(const Vector3& Other) const { return (this->x == Other.x) && (this->y == Other.y) && (this->z == Other.z); }
bool Vector3::operator!=(const Vector3& Other) const { return !(*this == Other); }
Vector3 Vector3::operator-() const { return Vector3(-this->x, -this->y, -this->z); }

std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
    os << "(" << vec.GetX() << ", " << vec.GetY() << ", " << vec.GetZ() << ")";
    return os;
}
