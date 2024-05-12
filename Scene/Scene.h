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
#include <emscripten.h>
#include <emscripten/html5.h>

#include "../Materials/Material.h"

class Scene {
    public:
      void render(Image* image);
      void initialize(Image* image);
      Camera& getCamera();
    const std::vector<std::shared_ptr<Object>>& getObjects() const;
    private:
        std::vector<std::shared_ptr<Object>> objects;
        std::vector<std::shared_ptr<Material>> materials;
        int width, height;

        Camera camera;
        Vector3 lightDir;
};
#endif