
#include "Scene.h"

void Scene::render(Image *image) {
    int width = image->getWidth();
    int height = image->getHeight();
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {

            float redRatio = static_cast<float>(x) / (width - 1);
            float greenRatio = static_cast<float>(y) / (height - 1);


            Uint8 red = static_cast<Uint8>(redRatio * 255);
            Uint8 green = static_cast<Uint8>(greenRatio * 255);
            Uint8 blue = 0;


            Color color(red, green, blue, 255,Image::pixel_format);
            image->setPixel(x, y, color.getMappedColor());
        }
    }
}
