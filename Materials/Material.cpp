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


    Material Material::from_json(const nlohmann::json& j) {



        // AMBIENT
        float ambient_r = j.at("Ambient_r").get<float>();
        float ambient_g = j.at("Ambient_g").get<float>();
        float ambient_b = j.at("Ambient_b").get<float>();
        float ambient_a = j.at("Ambient_a").get<float>();

        Color ambient = Color(ambient_r, ambient_g, ambient_b, ambient_a);

        // DIFFUSE
        float diffuse_r = j.at("Diffuse_r").get<float>();
        float diffuse_g = j.at("Diffuse_g").get<float>();
        float diffuse_b = j.at("Diffuse_b").get<float>();
        float diffuse_a = j.at("Diffuse_a").get<float>();

        Color diffuse = Color(diffuse_r, diffuse_g, diffuse_b, diffuse_a);

        // SPECULAR
        float specular_r = j.at("Specular_r").get<float>();
        float specular_g = j.at("Specular_g").get<float>();
        float specular_b = j.at("Specular_b").get<float>();
        float specular_a = j.at("Specular_a").get<float>();

        Color specular = Color(specular_r, specular_g, specular_b, specular_a);

        // Shininess and Ambient Strength
        float shininess = j.at("Shininess").get<float>();
        float ambientStrength = j.at("AmbientStrength").get<float>();

        return Material(ambient, diffuse, specular, shininess, ambientStrength);
    }


