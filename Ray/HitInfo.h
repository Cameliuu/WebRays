#ifndef HITINFO_H
#define HITINFO_H
#include "../Vector3/Vector3.h"
#include "../Ray/Ray.h"
#include <iostream>
#include "../Color/Color.h"
class HitInfo{
    public:
        HitInfo();
        HitInfo(const float& t1, const float& t2,const Ray& ray, const Vector3& origin, const Color& color);
        bool hit = false;
        Vector3 getT1Normal() const;
        Vector3 getT2Normal() const;
        Color getColor() const;
        float getT1() const ;
        float getT2() const ;
    private:
        float t1,t2;
        Vector3 t1WorldPosition,t2WorldPosition;
        Vector3 t1Normal,t2Normal;
        Color color;
};
#endif
