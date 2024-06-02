#ifndef MATERIAL_H
#define MATERIAL_H
#include "../Color/Color.h"
#include "../json.hpp"

class Material {
    public:
        Material(Color ambient, Color diffuse, Color specular, float shininess, float ambientS) : _ambient(ambient), _diffuse(diffuse), _specular(specular), _shininess(shininess), _ambientStrength(ambientS){}
                //GETTERS
        Color getAmbient() const;
        Color getDiffuse() const;
        Color getSpecular() const;
        float getShininess() const;
        float getAmbientStrength() const;
                //SETTERS
        void setAmbient(Color ambient);
        void setDiffuse(Color diffuse);
        void setSpecular(Color specular);
        void setShininess(float shininess);
                //JSON
    void from_json(const nlohmann::json& j, Material& obj);
    private:

        Color _ambient; // The ambient material vector defines what color the surface reflects under ambient lighting; this is usually the same as the surface's color
        Color _diffuse; //  The diffuse material vector defines the color of the surface under diffuse lighting. The diffuse color is (just like ambient lighting) set to the desired surface's color
        Color _specular; //  The specular material vector sets the color of the specular highlight on the surface (or possibly even reflect a surface-specific color)
        float _shininess; // Lastly, the shininess impacts the scattering/radius of the specular highlight.
        float _ambientStrength;
    // https://learnopengl.com/Lighting/Materials
    //http://devernay.free.fr/cours/opengl/materials.html
};



#endif