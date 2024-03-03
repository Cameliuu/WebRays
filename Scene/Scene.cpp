
#include "Scene.h"

void Scene::render(Image *image) {
    int width = image->getWidth();
    int height = image->getHeight();
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
            Color color(red, green, blue, 255,Image::pixel_format);
            image->setPixel(x, y, color.getMappedColor());
        }
    }
}
