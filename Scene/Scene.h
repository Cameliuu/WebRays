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
#include "../Lights/DirectionalLight.h"
#include <SDL.H>
#include <vector>
#include <memory>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <math.h>
#include "../Materials/Material.h"

class Scene {
    public:
      void render(Image* image);
      void initialize(Image* image);
      Camera& getCamera();
    const std::vector<std::shared_ptr<Object>>& getObjects() const;
    Color computeBRDF(HitInfo hit_info);
    float computeD(Vector3 surfaceNormal, Vector3 halfwayVector, float alpha);
    float G1(Vector3 N, Vector3 X, float alpha);
    float G(float alpha, Vector3 N, Vector3 V, Vector3 L);
    float F(float F0, Vector3 V, Vector3 H);
    Color traceRay(const Ray& ray, int depth);


    private:
        std::vector<std::shared_ptr<Object>> objects;
        std::vector<std::shared_ptr<Material>> materials;
        std::vector<std::shared_ptr<DirectionalLight>> lights;
        int width, height;

        Camera camera;

};
#endif