
#ifndef PLANE_H
#define PLANE_H
#include "Object.h"
#include "../Vector3/Vector3.h"
#include <emscripten/emscripten.h>
class Plane : public Object {
    public:
                        //CONSTRUCTOS
        Plane(Vector3 p0, Vector3 normal, std::shared_ptr<Material> material, short id);;
                        //GETTERS

        Vector3 getP0();
        Vector3 getNormal();
                        //SETTERS
        void setP0(Vector3 p0);
        void setNormal(Vector3 normal);

                        //METHODS
        HitInfo hit (const Ray& ray) const override;
        std::string getTypeString() const override;
    private:
        Vector3 _p0;
        Vector3 _normal;
};



#endif