
#include "HitInfo.h"

HitInfo::HitInfo(const float& t1, const float& t2, const Ray& ray, const Vector3& origin) {
    this->t1 = t1;
    this->t2 = t2;
    this->t1WorldPosition = ray.pointAtParameter(t1);
    this->t2WorldPosition = ray.pointAtParameter(t2);
    this->t1Normal = this->t1WorldPosition - origin;
    this->t1Normal.Normalize();
    this->t2Normal = this->t2WorldPosition - origin;
    this->t2Normal.Normalize();
}

Vector3 HitInfo::getT1Normal() const {
    return this->t1Normal;
}

Vector3 HitInfo::getT2Normal() const {
    return this->t2Normal;
}


