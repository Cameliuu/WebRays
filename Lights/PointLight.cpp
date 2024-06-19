
#include "PointLight.h"

Vector3 PointLight::getPosition() const
{
        return  this->_position;
}

Color PointLight::getColor () const
{
        return this->_color;
}
