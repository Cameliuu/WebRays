#ifndef OBJECT_H
#define OBJECT_H

#include "../Ray/Ray.h"
#include "../Ray/HitInfo.h"
#include "../Color/Color.h"
#include "../Materials/Material.h"
#include <memory>

class Object {
public:
    Object();
    Object(std::shared_ptr<Material> material);
    virtual HitInfo hit(const Ray& ray) const = 0;
    void setMaterial(std::shared_ptr<Material> material);
    std::shared_ptr<Material> getMaterial() const;

protected:
    std::shared_ptr<Material> material;
};

#endif
