#include "HitInfo.h"

HitInfo::HitInfo(const float& t1, const float& t2, const Ray& ray, const Vector3& origin, std::shared_ptr<Material> material)
    : t1(t1), t2(t2), incidenceRay(ray), material(material) {
    this->t1WorldPosition = ray.pointAtParameter(t1);
    this->t2WorldPosition = ray.pointAtParameter(t2);
    this->t1Normal = (this->t1WorldPosition - origin).Normalize();
    this->t2Normal = (this->t2WorldPosition - origin).Normalize();
}

Vector3 HitInfo::getT1Normal() const {
    return this->t1Normal;
}

Vector3 HitInfo::getT2Normal() const {
    return this->t2Normal;
}

Vector3 HitInfo::getT1WorldPost() const {
    return this->t1WorldPosition;
}

std::shared_ptr<Material> HitInfo::getMaterial() const {
    return this->material;
}

float HitInfo::getT1() const {
    return this->t1;
}

float HitInfo::getT2() const {
    return this->t2;
}

Ray HitInfo::getIncidenceRay() const {
    return this->incidenceRay;
}


