#ifndef OBJECT_H
#define OBJECT_H
#include "../Ray/Ray.h"
#include <SDL.h>
#include "../Ray/HitInfo.h"
#include <cmath>
class Object{
    public:
        virtual HitInfo hit(const Ray& ray) const = 0;
        void setColor(const Uint32& color);
        Uint32 getColor() const;

    private:
        Uint32 color;
};

#endif