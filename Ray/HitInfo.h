#ifndef HITINFO_H
#define HITINFO_H

#include "../Vector3/Vector3.h"
#include "../Ray/Ray.h"
#include "../Materials/Material.h"
#include <iostream>
#include <memory>

class HitInfo {
public:
    HitInfo() = default;
    HitInfo(const float& t1, const float& t2, const Ray& ray, const Vector3& origin, std::shared_ptr<Material> material);
    bool hit = false;
    Vector3 getT1Normal() const;
    Vector3 getT2Normal() const;
    Vector3 getT1WorldPost() const;
    std::shared_ptr<Material> getMaterial() const;
    float getT1() const;
    float getT2() const;
    Ray getIncidenceRay() const;
private:
    float t1, t2;
    Vector3 t1WorldPosition, t2WorldPosition;
    Vector3 t1Normal, t2Normal;
    std::shared_ptr<Material> material;
    Ray incidenceRay;
};

#endif
