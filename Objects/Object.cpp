#include "Object.h"

Object::Object() {}

Object::Object(short id)
{
    this->id = id;
}

Object::Object(Material& material, short id)
{
    this->material = std::make_shared<Material>(material);
    this->id = id;
}

Object::Object(std::shared_ptr<Material> material, short id) : material(material), id(id) {}

HitInfo Object::hit(const Ray& ray) const {
    // Implement hit function for your specific object
}

void Object::setMaterial(std::shared_ptr<Material> material) {
    this->material = material;
}

std::shared_ptr<Material> Object::getMaterial() const {
    return this->material;
}

short Object::getId()
{
    return this->id;
}


