#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "../Vector3/Vector3.h"
#include <emscripten.h>


class Sphere : public Object {
    public:
        Sphere(const Vector3 &center, const float &radius, Material& material , short id);
        Sphere(const Vector3 &center, const float &radius, std::shared_ptr<Material> material , short id);
        Sphere(const Vector3 &center, const float &radius , short id);
        HitInfo hit (const Ray& ray) const override;
        void setCenter(const Vector3& center);
        void setRadius(const float& radius);
        Vector3 getCenter() const ;
        float getRadius() const;
        static Sphere from_json(const nlohmann::json& j);
    private:
        Vector3 center;
        float radius;

};
#endif