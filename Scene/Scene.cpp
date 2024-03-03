
#include "Scene.h"

void Scene::render(Image *image) {
    int width = image->getWidth();
    int height = image->getHeight();
    // Simulate creating the sphere
    Vector3 sphereCenter(0.0f, 0.0f, -1.0f);  // Example sphere center
    float sphereRadius = 0.1f;  // Example sphere radius
    sphere.setCenter(sphereCenter);
    sphere.setRadius(sphereRadius);


    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            //Get U and V normalized coordinates
            // (0,1)
            float u = (float)x / (float)(width-1);
            float v = (float)y / (float)(height-1);

            //Create the RAY
            Vector3 origin = Vector3(0.0f, 0.0f, 0.0f);
            Vector3 direction = Vector3(u - 0.5f, v - 0.5f, -1.0f);

            Ray ray = Ray(origin, direction);
            Uint8 red = static_cast<Uint8>(ray.getDirection().GetX() * 255.0f);
            Uint8 green = static_cast<Uint8>(ray.getDirection().GetY() * 255.0f);
            Uint8 blue = 128;
            Color color = Color();
            HitInfo hitInfo = sphere.hit(ray);
            if(hitInfo.hit)
            {
                // Calculate a simple diffuse lighting component based on the normal
                Vector3 lightDir = Vector3(0.0f, 0.0f, -1.0f); // For simplicity, assume light comes from the same direction as the camera
                lightDir.Normalize(); // Make sure the light direction is normalized

                // The dot product between the normal at intersection and light direction
                float dot = lightDir.Dot(hitInfo.getT1Normal());
                float intensity = std::max(dot, 0.0f); // Clamp the value between 0 and 1
                //HIT
                color.setColor(255,0,0,255*intensity,Image::pixel_format);
            }
            else{
                color.setColor(red,green,blue,255,Image::pixel_format);
                //MISS
            }


            image->setPixel(x, y, color.getMappedColor());
        }
    }
}
