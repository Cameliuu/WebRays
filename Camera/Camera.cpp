

#include "Camera.h"

Camera::Camera() {

}

void Camera::setPosition(const Vector3 &position) {
    this->position = position;
}

void Camera::setLookAt(const Vector3 &look_at) {

}

void Camera::setAspectRatio(const float &aspect_ratio) {
    this->aspect_ratio = aspect_ratio;
}

void Camera::setFov(const float &fov) {
    this->fov = fov;
}

Vector3 Camera::getPosition() const {
    return this->position;
}

Vector3 Camera::getLookAt() const {
    return this->look_at;
}

float Camera::getFov() const {
    return this->fov;
}

float Camera::getAspectRatio() const {
    return this->aspect_ratio;
}

Ray Camera::shootRay(float u, float v) {
    //Calculate NDC
    float pixel_ndc_x = u-0.5f;
    float pixel_ndc_y = v-0.5f;

    //Calculate Pixel Screen coordinates
    float pixel_screen_x = 2.0f*pixel_ndc_x * aspect_ratio;
    float pixel_screen_y = 2.0f*pixel_ndc_y;


    //Create the RAY vectors
    Vector3 origin = this->position;
    Vector3 direction = Vector3(pixel_screen_x, pixel_screen_y, -1.0f);
    direction = direction.Normalize();

    return Ray(origin, direction);
}

void Camera::setPoisitionX(const float &x) {
    this->position.SetX(x);
}

void Camera::setPoisitionY(const float &y) {
    this->position.SetY(y);
}

void Camera::setPoisitionZ(const float &z) {
    this->position.SetZ(z);
}
