

    #include "Sphere.h"

    HitInfo Sphere::hit(const Ray &ray) const {
        Vector3 oc = ray.getOrigin() - center;  // Vector from ray origin to sphere center
        float a = ray.getDirection().Dot(ray.getDirection());  // Dot product of ray direction with itself, equivalent to the square of the length
        float b = 2.0 * oc.Dot( ray.getDirection());  // 2 times dot product of oc and ray direction
        float c = oc.Dot(oc) - radius * radius;  // Dot product of oc with itself minus radius squared
        float discriminant = b * b - 4 * a * c;  // Discriminant of the quadratic equation
        float t1 = (float)(-b + sqrt( discriminant) )/ 2*a;
        float t2 = (float)(-b - sqrt( discriminant) )/ 2*a;
        HitInfo hitInfo = HitInfo(t1,t2,ray,this->center,this->getMaterial(),this->id);
        if(discriminant > 0)
        {
            hitInfo.hit = true;
        }
        else
        {
            hitInfo.hit = false;
        }

        return hitInfo;
    }

    void Sphere::setCenter(const Vector3 &center) {
        this->center = center;
    }


void Sphere::setRadius(const float &radius) {
        this->radius = radius;
    }

    Vector3 Sphere::getCenter() const {
        return this->center;
    }

    float Sphere::getRadius() const {
        return this->radius;
    }

    Sphere::Sphere(const Vector3 &center, const float &radius, std::shared_ptr<Material> material,short id) : Object(material,id) {
        this->center = center;
        this->radius = radius;
    }


