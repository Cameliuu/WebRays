

#ifndef LIGHT_H
#define LIGHT_H
#include "../Vector3/Vector3.h"
#include "../Color/Color.h"
class DirectionalLight {
    public:
                                    //CONSTRUCTORS
    DirectionalLight(Vector3 direction, Color color) : _diretion(direction), _color(color){}
                                    //GETTERS

    Vector3 getDirection();
    Color getColor();

                                //SETTERS

    void setDirection(Vector3 direction);
    void setColor(Color color);
    private:

        Vector3 _diretion;
        Color _color;
};



#endif
