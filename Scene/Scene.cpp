#include "Scene.h"
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding rand()

#include "../App/App.h"
#include "../Lights/DirectionalLight.h"
#include "../Objects/Plane.h"

inline float fast_rand() {
    static thread_local uint32_t seed = 123456789;
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed / float(UINT32_MAX);
}

void Scene::render(Image* image) {
            const int samples_per_pixel = 4; // Number of samples per pixel for anti-aliasing
    std::srand(static_cast<unsigned int>(std::time(0))); // Seed the random number generator

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            float accumulated_red = 0.0f;
            float accumulated_green = 0.0f;
            float accumulated_blue = 0.0f;

            // Take multiple samples per pixel
            for (int s = 0; s < samples_per_pixel; ++s) {
                // Generate random offsets for supersampling
                float u = (x + static_cast<float>(fast_rand()) / (static_cast<float>(RAND_MAX) + 1)) / (width - 1);
                float v = (y + static_cast<float>(fast_rand()) / (static_cast<float>(RAND_MAX) + 1)) / (height - 1);

                Ray ray = camera.shootRay(u, v);
                Color color = traceRay(ray, 4); // Start tracing the primary ray with a depth of 4

                accumulated_red += color.getRedValue();
                accumulated_green += color.getGreenValue();
                accumulated_blue += color.getBlueValue();

            }

            // Average the colors
            Uint8 final_red = static_cast<Uint8>(accumulated_red / samples_per_pixel);
            Uint8 final_green = static_cast<Uint8>(accumulated_green / samples_per_pixel);
            Uint8 final_blue = static_cast<Uint8>(accumulated_blue / samples_per_pixel);

            Color final_color(final_red, final_green, final_blue, 255);

            image->setPixel(x, y, final_color.getMappedColor());
        }
    }
}











Color Scene::traceRay(const Ray& ray, int depth) {
    if (depth <= 0) {
        return Color(0, 0, 0, 255); // Return black if maximum depth is reached
    }

    float min_t = std::numeric_limits<float>::infinity();
    HitInfo closest_hit_info;
    closest_hit_info.hit = false;

    // Loop through each object to find the closest hit
    for (const auto& object : objects) {
        HitInfo hitInfo = object->hit(ray);

        if (hitInfo.hit) {
            float t1 = hitInfo.getT1();
            if (t1 >= 0 && t1 < min_t) {  // Check if this hit is closer
                min_t = t1;
                closest_hit_info = hitInfo;
            }
        }
    }

    // If there is a hit, calculate the color
    if (closest_hit_info.hit) {
        Color final_color(0, 0, 0, 255);
        for (std::shared_ptr<PointLight> light : lights) {
            // Ambient
            Color ambient = light->getColor() * closest_hit_info.getMaterial()->getAmbient() * closest_hit_info.getMaterial()->getAmbientStrength();
            final_color = final_color + ambient;



            bool inShadow = false;



                Vector3 lightDir = (light->getPosition() - closest_hit_info.getT1WorldPost()).Normalize();


                // Diffuse
                Vector3 normal = closest_hit_info.getT1Normal().Normalize();
                float diff = std::max(normal.Dot(lightDir), 0.0f);
                Color diffuse = light->getColor() * (closest_hit_info.getMaterial()->getDiffuse() * diff);

                //Specular
                Vector3 viewDir = (camera.getPosition() - closest_hit_info.getT1WorldPost()).Normalize();
                Vector3 reflectDir = (normal * (normal.Dot(lightDir)) * 2.0f) - lightDir;
                float spec = pow(std::max(viewDir.Dot(reflectDir), 0.0f), closest_hit_info.getMaterial()->getShininess());
                Color specular = light->getColor() * (closest_hit_info.getMaterial()->getSpecular() * spec);


                final_color = final_color + diffuse + specular;

        }

        return final_color;
    }

    // Return background color if no hit
    return Color(125, 0, 0, 255);
}

void Scene::load_from_config_file()
{
    App::loadingDone = false;
    //CLEAR THE VECTORS
    objects.clear();
    materials.clear();
    //Load the json

    std::string json = App::ReadAllText(App::configFile);
    load_materials(json);
    load_objects(json);
    App::loadingDone = true;
}


void Scene::load_materials(std::string json)
{
    // Parse the JSON data
    nlohmann::json j = nlohmann::json::parse(json);

    for (const auto& item : j.at("Materials")) {
        Material material = Material::from_json(item);
        materials.push_back(std::make_shared<Material>(material));
    }
}

void Scene::load_objects(std::string json)
{

    nlohmann::json j = nlohmann::json::parse(json);

    for (const auto& item : j.at("Spheres")) {

        Sphere sphere = Sphere::from_json(item);
        emscripten_log(EM_LOG_CONSOLE, "Center x : %f", sphere.getCenter().GetX());
        emscripten_log(EM_LOG_CONSOLE, "Center y : %f", sphere.getCenter().GetY());
        emscripten_log(EM_LOG_CONSOLE, "Center z : %f", sphere.getCenter().GetZ());
        short materialIndex = item.at("MaterialIndex").get<short>();
        sphere.setMaterial(materials.at(materialIndex));
        objects.push_back(std::make_shared<Sphere>(sphere));
    }
}


void Scene::initialize(Image* image) {

  // load_from_config_file();
    for (const auto& material : materials) {
        emscripten_log(EM_LOG_CONSOLE, "Material:");
        emscripten_log(EM_LOG_CONSOLE, "  Ambient: %s", material->getAmbient().getColorString().c_str());
        emscripten_log(EM_LOG_CONSOLE, "  Diffuse: %s", material->getDiffuse().getColorString().c_str());
        emscripten_log(EM_LOG_CONSOLE, "  Specular: %s", material->getSpecular().getColorString().c_str());
        emscripten_log(EM_LOG_CONSOLE, "  Shininess: %f", material->getShininess());
        emscripten_log(EM_LOG_CONSOLE, "  Ambient Strength: %f", material->getAmbientStrength());
    }
    // Create and initialize the materials

    Vector3 lightPos =  Vector3(-0.7f, -0.2f, -1.0f);
    // Simulate creating the spheres
    Vector3 sphereCenter1(0.35f, 0.0f, -1.0f); // Position the sphere further away
    Vector3 sphereCenter2(-0.35f, 0.4f, -1.0f); // Position the sphere further away
    Vector3 planeCenter(0.0f, 1.0f, -1.0f); // Adjust position of the plane
    Vector3 planeNormal(0.0f, 1.0f, 0.0f); // Adjust normal of the plane
    float sphereRadius = 0.4f;


    objects.push_back(std::make_shared<Sphere>(lightPos,0.1f,std::make_shared<Material>(Material(Color::Red,Color::Red,Color::White,256,12)),7));
   // objects.push_back(std::make_shared<Plane>(Vector3(-3.0f, 1.0f, 3.0f), Vector3(-1.0f, 0.0f, 0.0f), materials.at(1), 5));
  // objects.push_back(std::make_shared<Plane>(Vector3(0.0f, -1.0f, 2.0f), Vector3(0.0f, 1.0f, 0.0f), materials.at(1), 2)); // Floor
   // objects.push_back(std::make_shared<Plane>(Vector3(0.0f, 1.0f, 2.0f), Vector3(0.0f, -1.0f, 0.0f), materials.at(1), 3)); // Ceiling
    //objects.push_back(std::make_shared<Plane>(Vector3(0.0f, 0.0f, -1.0f), Vector3(0.0f, 0.0f, 1.0f), materials.at(1), 4)); // Back Wall
     // Adjusted position to match the center
; // Left Wall
    //objects.push_back(std::make_shared<Plane>(Vector3(1.0f, 0.0f, -1.0f), Vector3(-1.0f, 0.0f, 0.0f), materials.at(1), 6)); // Right Wall

   // objects.push_back(std::make_shared<Plane>(-Vector3(2.0f, 0.0f, -2.0f),Vector3(-1.0f,0.0f,0.0f),materials.at(1),6));
    this->width = image->getWidth();
    this->height = image->getHeight();

    // Create and initialize the light


    this->lights.push_back(std::make_shared<PointLight>(lightPos,Color::White));

    // Create and initialize the camera
    Vector3 origin = Vector3(0.0f, 0.0f, 1.0f); // Move the camera back
    camera.setAspectRatio(static_cast<float>(width) / static_cast<float>(height));
    camera.setPosition(origin);
   // camera.setLookAt();
    camera.setPitch(0); // Adjust as needed
    camera.setYaw(0);   // Adjust as needed
    emscripten_log(EM_LOG_CONSOLE, "Scene initialized with %d objects", objects.size());
    for(const auto& object : objects)
    {
        emscripten_log(EM_LOG_CONSOLE, "Object ID: %d", object->getId());
    }
}

Camera& Scene::getCamera() {
    return this->camera;
}

 std::vector<std::shared_ptr<Object>>& Scene::getObjects() {
    return this->objects;
}
