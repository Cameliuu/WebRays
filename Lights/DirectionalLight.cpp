//
// Created by Mabeshau on 5/25/2024.
//

#include "DirectionalLight.h"



Vector3 DirectionalLight::getDirection()
{
    return this -> _diretion;
}

Color DirectionalLight::getColor()
{
    return this->_color;
}


void DirectionalLight::setDirection(Vector3 direction)
{
    this->_diretion = direction;
}

void DirectionalLight::setColor(Color color)
{
    this->_color = color;
}
