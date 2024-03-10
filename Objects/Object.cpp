

#include "Object.h"

Color Object::getColor() const {
    return this->color;
}

void Object::setColor(const Color &color) {
    this->color = color;
}

Object::Object() {

}

Object::Object(const Color &color) {
    this->color = color;
}
