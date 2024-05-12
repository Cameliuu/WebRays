#include "Object.h"

Object::Object() {}

Object::Object(std::shared_ptr<Material> material) : material(material) {}

HitInfo Object::hit(const Ray& ray) const {
    // Implement hit function for your specific object
}

void Object::setMaterial(std::shared_ptr<Material> material) {
    this->material = material;
}

std::shared_ptr<Material> Object::getMaterial() const {
    return this->material;
}
