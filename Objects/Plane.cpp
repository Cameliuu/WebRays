

#include "Plane.h"

Plane::Plane(Vector3 p0, Vector3 normal, std::shared_ptr<Material> material, short id)
{
    this->_p0 = p0;
    this->_normal = normal;
    this->material = material;
    this->id = id;
}

Vector3 Plane::getP0()
{
    return this-> _p0;
}

Vector3 Plane::getNormal()
{
    return this-> _normal ;
}

void Plane::setP0(Vector3 p0)
{
    this->_p0 = p0;
}

void Plane::setNormal(Vector3 normal)
{
    this->_normal = normal;
}

HitInfo Plane::hit(const Ray& ray) const
{
    Vector3 l0 = ray.getOrigin();
    Vector3 l = ray.getDirection();
    float denominator = l.Dot(_normal);
    float t = 0.0;
    HitInfo hit(t,0.0f,ray,_p0,this->material,this->id);
    if(fabs(denominator) > 1e-6) // avoid divsion by 0
    {
        Vector3 p0l0 = _p0-l0;
        t = p0l0.Dot(_normal) / denominator;

        if(t > 0)
        {
            hit.hit = true;
            hit.setT1(t);
        }
        else
            hit.hit = false;

    }
    return hit;
}


