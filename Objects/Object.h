#ifndef OBJECT_H
#define OBJECT_H
#include "../Ray/Ray.h"
#include <SDL.h>
#include "../Ray/HitInfo.h"
#include <cmath>
#include "../Color/Color.h"
class Object{
    public:
        Object();
        Object(const Color& color);
        virtual HitInfo hit(const Ray& ray) const = 0;
        void setColor(const Color& color);
        Color getColor() const;

    protected:
        Color color;
};

#endif