#pragma once
#include <ostream>

#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
public:
    // CONSTRUCTORS
    Vector3();
    Vector3(float x, float y, float z);

    // DESTRUCTORS
    ~Vector3();

    // GETTERS
    float GetX() const;
    float GetY() const;
    float GetZ() const;

    // SETTERS
    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);

    // METHODS
    float Magnitude() const;
    float Dot(const Vector3& Other) const;
    Vector3 Normalize() const;

    // OPERATOR OVERLOADS
    Vector3 operator+(const Vector3& Other) const;
    Vector3 operator-(const Vector3& Other) const;
    Vector3 operator*(const float value) const;
    Vector3 operator-() const;
    bool operator==(const Vector3& Other) const;
    bool operator!=(const Vector3& Other) const;
    friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);

private:
    float x, y, z;
};

#endif
