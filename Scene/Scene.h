#ifndef SCENE_H
#define SCENE_H
#include "../Image/Image.h"
#include <SDL.h>
#include "../Ray/ray.h"
#include "../Objects/Sphere.h"
#include <emscripten.h>
#include "../Camera/Camera.h"
#include <emscripten/wasm_worker.h>
#include "../Color/Color.h"
#include <SDL.H>
#include <vector>
#include <memory>
class Scene {
    public:
      void render(Image* image);
      void initialize(Image* image);
    private:
        std::vector<std::shared_ptr<Object>> objects;
        int width, height;

        Camera camera;
        Vector3 lightDir;
};
#endif