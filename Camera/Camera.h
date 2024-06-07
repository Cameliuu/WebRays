#ifndef CAMERA_H
#define CAMERA_H
#include "../Vector3/Vector3.h"
#include "../Ray/Ray.h"
#include <math.h>
class Camera{
    public:
                    //CONSTRUCTORS
        Camera();
                    //SETTERS
        void setPosition(const Vector3& position);
        void setLookAt(const Vector3& look_at);
        void setAspectRatio(const float& aspect_ratio);
        void setFov(const float& fov);
        void setPoisitionX(const float& x);
        void setPoisitionY(const float& Y);
        void setPoisitionZ(const float& Z);
        void setYaw(const float& yaw);
        void setPitch(const float& pitch);
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
    Vector3 up;
    Vector3 right;
    Vector3 forward;
    void updateCameraVectors();
    float aspect_ratio;
    float fov;
    float pitch;
    float yaw;
};
#endif