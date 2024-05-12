
#ifndef MATERIAL_H
#define MATERIAL_H
#include "../Color/Color.h"


class Material {
    public:
        Material(Color albedo, float roughness, float metallic) : _albedo(albedo) , _roughness(roughness) , _metallic(metallic){}
                            //GETTERS
        Color getAlbedo();
        float getRoughness();
        float getMetallicValue();
                            //SETTERS
        void setAlbedo(Color albedo);
        void setRoughness(float roughness);
        void setMetallicValue(float metallic);
    private:
        Color _albedo;
        float _roughness;
        float _metallic;
};



#endif
