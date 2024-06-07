
#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "../Vector3/Vector3.h"
#include "../Color/Color.h"

class PointLight {
    public:
        PointLight(Vector3 position, Color color) : _position(position), _color(color){}
    //GETTERS

    Vector3 getPosition();
    Color getColor();
    private:
        Vector3 _position;
        Color _color;
};



#endif
