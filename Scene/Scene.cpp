
#include "Scene.h"

void Scene::render(Image* image) {
    Color color;
    float min_t;
    HitInfo closest_hit_info;


    // Initialize the closest hit distance to a large number
    min_t = std::numeric_limits<float>::infinity();

    // Loop through each pixel
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            float u = static_cast<float>(x) / (width - 1);
            float v = static_cast<float>(y) / (height - 1);

            Ray ray = camera.shootRay(u, v);

            // Reset the closest hit for this pixel
            closest_hit_info.hit = false;
            min_t = std::numeric_limits<float>::infinity();

            // Loop through each object to find the closest hit
            for (int i = 0; i < objects.size(); i++) {
                HitInfo hitInfo = objects.at(i)->hit(ray);

                if (hitInfo.hit) {
                    float t1 = hitInfo.getT1();
                    if (t1 >= 0 && t1 < min_t) {  // Check if this hit is closer
                        min_t = t1;
                        closest_hit_info = hitInfo;
                    }
                }
            }

            // Color the pixel based on the closest hit
            if (closest_hit_info.hit) {
                Vector3 normal = closest_hit_info.getT1Normal();
                float dot = std::max(normal.Dot(lightDir), 0.0f);

                Uint8 red = static_cast<Uint8>(dot * closest_hit_info.getMaterial()->getAlbedo().getRedValue());
                Uint8 green = static_cast<Uint8>(dot * closest_hit_info.getMaterial()->getAlbedo().getGreenValue());
                Uint8 blue = static_cast<Uint8>(dot * closest_hit_info.getMaterial()->getAlbedo().getBlueValue());

                color.setColor(red, green, blue, 255, Image::pixel_format);
            } else {
                color.setColor(135, 206, 235, 255, Image::pixel_format);
            }

            image->setPixel(x, y, color.getMappedColor());
        }
    }
}

void Scene::initialize(Image* image) {

    //Create and initialize the materials
    materials.push_back(std::make_shared<Material>(Color::Green,1.0f,0.0f));
    materials.push_back(std::make_shared<Material>(Color::Blue,0.0f,0.0f));

    // Simulate creating the sphere
    Vector3 sphereCenter1(1.0f, 0.0f, -1.0f);  // Example sphere center
    Vector3 sphereCenter2(0.0f, 0.0f, -1.5f);  // Example sphere center
    float sphereRadius = 0.1f;  // Example sphere radius
    objects.push_back(std::make_shared<Sphere>(sphereCenter1, sphereRadius,materials.at(0)));
    objects.push_back(std::make_shared<Sphere>(sphereCenter2, sphereRadius, materials.at(1)));


    this->width = image->getWidth();
    this-> height = image->getHeight();


    //Create and initialize the light
    Vector3 lightDir = -(Vector3(-0.25f, -0.25f, 2.0f) - sphereCenter1);
    lightDir = lightDir.Normalize();
    this->lightDir = lightDir;

    //Create and initialize the camera
    Vector3 origin = Vector3(0.0f, 0.0f, 0.0f);
    camera.setAspectRatio((float) width / (float) height);
    camera.setPosition(origin);
    camera.setPitch(0);
    camera.setYaw(0);

}

Camera &Scene::getCamera() {
    return this->camera;
}

const std::vector<std::shared_ptr<Object>>& Scene::getObjects() const
{
    return this->objects;
}


