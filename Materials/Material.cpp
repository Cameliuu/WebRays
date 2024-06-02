//
// Created by Mabeshau on 5/12/2024.
//

#include "Material.h"

Color Material::getAmbient() const
{
    return this->_ambient;
}

Color Material::getDiffuse() const
{
    return  this->_diffuse;
}

Color Material::getSpecular() const
{
    return this->_specular;
}

float Material::getShininess() const
{
    return this->_shininess;
}

float Material::getAmbientStrength() const
{
    return this->_ambientStrength;
}

void Material::setAmbient(Color ambient)
{
    this->_ambient = ambient;
}

void Material::setDiffuse(Color diffuse)
{
    this -> _diffuse = diffuse;
}

void Material::setSpecular(Color specular)
{
    this->_specular = specular;
}

void Material::setShininess(float shininess)
{
    this->_shininess = shininess;
}

void Material::from_json(const nlohmann::json& j, Material& obj)
{

}
