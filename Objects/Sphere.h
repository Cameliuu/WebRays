#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "../Vector3/Vector3.h"


class Sphere : public Object {
    public:
        Sphere(const Vector3& center, const float& radius, const Color& color);
        HitInfo hit (const Ray& ray) const override;
        void setCenter(const Vector3& center);
        void setRadius(const float& radius);
        Vector3 getCenter() const ;
        float getRadius() const;
        Color getColor() const;
    private:
        Vector3 center;
        float radius;

};
#endif