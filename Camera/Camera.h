#ifndef CAMERA_H
#define CAMERA_H
#include "../Vector3/Vector3.h"
#include "../Ray/Ray.h"
class Camera{
    public:
                    //CONSTRUCTORS
        Camera();
                    //SETTERS
        void setPosition(const Vector3& position);
        void setLookAt(const Vector3& look_at);
        void setAspectRatio(const float& aspect_ratio);
        void setFov(const float& fov);
                    //GETTERS
        Vector3 getPosition() const;
        Vector3 getLookAt() const;
        float getFov() const;
        float getAspectRatio() const;

                //PUBLIC METHODS
        Ray  shootRay(float u,float v);
    private:
    Vector3 position;
    Vector3 look_at;
    float aspect_ratio;
    float fov;
};
#endif