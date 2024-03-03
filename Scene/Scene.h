#ifndef SCENE_H
#define SCENE_H
#include "../Image/Image.h"
#include <SDL.h>
#include "../Ray/ray.h"
class Scene {
    public:
      void render(Image* image);
    private:
};
#endif