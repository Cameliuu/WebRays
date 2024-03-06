
#include "Scene.h"

void Scene::render(Image *image) {
    int width = image->getWidth();
    int height = image->getHeight();

    // Simulate creating the sphere
    Vector3 sphereCenter(0.0f, 0.0f, -1.0f);  // Example sphere center
    float sphereRadius = 0.1f;  // Example sphere radius
    sphere.setCenter(sphereCenter);
    sphere.setRadius(sphereRadius);

                //Create and initialize the camera
    Vector3 origin = Vector3(1.0f, 0.5f,0.0f);
    camera.setAspectRatio((float)width/(float)height );
    camera.setPosition(origin);

    Vector3 lightDir = -(Vector3(-0.25f, -0.25f, 2.0f) - sphereCenter);

    lightDir = lightDir.Normalize();

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            //Get U and V normalized coordinates
            // (0,1)
            float u = (float)x / (float)(width-1);
            float v = (float)y / (float)(height-1);



            //Vector3 direction = Vector3(u - 0.5f, v - 0.5f, -1.0f);

            Ray ray = camera.shootRay(u,v);
            Uint8 red = static_cast<Uint8>(ray.getDirection().GetX() * 255.0f);
            Uint8 green = static_cast<Uint8>(ray.getDirection().GetY() * 255.0f);
            Uint8 blue = 128;
            Color color = Color();
            HitInfo hitInfo = sphere.hit(ray);
            if(hitInfo.hit)
            {
                Vector3 normal = hitInfo.getT1Normal();
                // Light coming from the camera
                float dot = std::max(normal.Dot(lightDir), 0.0f); // Dot product, clamped to the range [0, 1]
                //if(dot > 0.0f)
                //if(x%100==0)
                //emscripten_log(EM_LOG_CONSOLE,"dot :%f\n",dot);
                // Assuming your light color is white for simplicity
                Uint8 red = static_cast<Uint8>(dot * 255);
                Uint8 green = static_cast<Uint8>(dot * 255);
                Uint8 blue = static_cast<Uint8>(dot * 255);

                // Now we use these to set the color
                color.setColor(red, 0, 0, 255,Image::pixel_format); // Omitting the pixel format for simplicity
            }
            else{
                color.setColor(0,0,0,255,Image::pixel_format);
                //MISS
            }


            image->setPixel(x, y, color.getMappedColor());
        }
    }
}
