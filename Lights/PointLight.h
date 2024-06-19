#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "../Vector3/Vector3.h"
#include "../Color/Color.h"

class PointLight {
public:
    PointLight(Vector3 position, Color color, float constantAttenuation, float linearAttenuation, float quadraticAttenuation)
        : _position(position), _color(color), _constantAttenuation(constantAttenuation),
          _linearAttenuation(linearAttenuation), _quadraticAttenuation(quadraticAttenuation) {}

    // Getters
    Vector3 getPosition() const ;
    Color getColor() const ;
    float getAttenuationConstant() const { return _constantAttenuation; }
    float getAttenuationLinear() const { return _linearAttenuation; }
    float getAttenuationQuadratic() const { return _quadraticAttenuation; }

private:
    Vector3 _position;
    Color _color;
    float _constantAttenuation;
    float _linearAttenuation;
    float _quadraticAttenuation;
};

#endif
