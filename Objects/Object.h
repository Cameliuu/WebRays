#ifndef OBJECT_H
#define OBJECT_H

#include "../Ray/Ray.h"
#include "../Ray/HitInfo.h"
#include "../Color/Color.h"
#include "../Materials/Material.h"
#include <memory>
#include <math.h>
class Object {
public:
    Object();
    Object(short id);
    Object(std::shared_ptr<Material> material, short id);
    virtual HitInfo hit(const Ray& ray) const = 0;
    void setMaterial(std::shared_ptr<Material> material);
    std::shared_ptr<Material> getMaterial() const;
    short getId();
    void setPosition(const Vector3& vector3);

protected:
    std::shared_ptr<Material> material;
    short id;
private:

};

#endif
