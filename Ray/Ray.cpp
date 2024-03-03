

#include "Ray.h"

Ray::Ray(const Vector3 &origin, const Vector3 &direction)
{
    this->origin = origin;
    this->direction = direction;
}

Vector3 Ray::pointAtParameter(float t) const {
    // P(T) = O + D*T
    return this->origin + this->direction * t;
}

Vector3 Ray::getDirection() const {
    return this->direction;
}

Vector3 Ray::getOrigin() const {
    return this->origin;
}


