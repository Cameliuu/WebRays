//
// Created by Mabeshau on 5/12/2024.
//

#include "Material.h"

Color Material::getAlbedo()
{
    return this->_albedo;
}

float Material::getRoughness()
{
    return this->_roughness;
}

float Material::getMetallicValue()
{
    return this->_metallic;
}

void Material::setAlbedo(Color albedo)
{
    this->_albedo = albedo;
}

void Material::setRoughness(float roughness)
{
    this -> _roughness = roughness;
}

void Material::setMetallicValue(float metallic)
{
    this -> _metallic = metallic;
}