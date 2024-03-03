#ifndef RAY_H
#define RAY_H
#include "../Vector3/Vector3.h"
class Ray{
    public:
    Ray(const Vector3& origin, const Vector3& direction);
    Vector3 pointAtParameter(float t) const;
    Vector3 getDirection() const;
    Vector3 getOrigin() const;

    private:
    Vector3 origin;
    Vector3 direction;
};
#endif