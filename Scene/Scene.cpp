#include "Scene.h"
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding rand()

void Scene::render(Image* image) {
            const int samples_per_pixel = 16; // Number of samples per pixel for anti-aliasing
    std::srand(static_cast<unsigned int>(std::time(0))); // Seed the random number generator

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            float accumulated_red = 0.0f;
            float accumulated_green = 0.0f;
            float accumulated_blue = 0.0f;

            // Take multiple samples per pixel
            for (int s = 0; s < samples_per_pixel; ++s) {
                // Generate random offsets for supersampling
                float u = (x + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) + 1)) / (width - 1);
                float v = (y + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) + 1)) / (height - 1);

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

            Color final_color(final_red, final_green, final_blue, 255, Image::pixel_format);
            image->setPixel(x, y, final_color.getMappedColor());
        }
    }
}
Color Scene::traceRay(const Ray& ray, int depth) {
    if (depth <= 0) {
        return Color(0, 0, 0, 255, Image::pixel_format); // Return black if maximum depth is reached
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
    //When calculating lighting we usually do not care about the magnitude of a vector or their position;
    //we only care about their direction.
    //Because we only care about their direction almost all the calculations are done with unit vectors
    //since it simplifies most calculations (like the dot product). So when doing lighting calculations,
    //make sure you always normalize the relevant vectors to ensure they're actual unit vectors.
    //Forgetting to normalize a vector is a popular mistake.
    if (closest_hit_info.hit) {
       //ambient
        Color ambient =  lightColor * closest_hit_info.getMaterial()->getAmbient() * 0.1f;

        //diffuse
        Vector3 normal = closest_hit_info.getT1Normal();
        float diff = std::max(normal.Dot(lightDir),0.0f);
        Color diffuse =  lightColor * (closest_hit_info.getMaterial()->getDiffuse() * diff);

        //specular
        Vector3 lightDirection = - lightDir;
        Vector3 viewDir = (camera.getPosition() - closest_hit_info.getT1Normal()).Normalize();

        Vector3 reflectDir = (normal*(normal.Dot(lightDirection)) * 2.0f) - lightDirection;
        float spec = pow(std::max(viewDir.Dot(reflectDir),0.0f),closest_hit_info.getMaterial()->getShininess());
        Color specular = lightColor * (closest_hit_info.getMaterial()->getSpecular() * spec);
        return ambient + diffuse + specular;
    }

    // Return background color if no hit
    return Color(0, 0, 0, 0, Image::pixel_format);
}

void Scene::initialize(Image* image) {
    // Create and initialize the materials
    materials.push_back(std::make_shared<Material>(Color::Red, Color::Red, Color::White,256.0f));
    materials.push_back(std::make_shared<Material>(Color::Green, Color::Green, Color::White,32.0f));

    // Simulate creating the spheres
    Vector3 sphereCenter1(0.35f, 0.0f, -1.0f); // Position the sphere further away
    Vector3 sphereCenter2(-0.35f, 0.4f, -1.0f); // Position the sphere further away
    float sphereRadius = 0.4f;
    objects.push_back(std::make_shared<Sphere>(sphereCenter1, sphereRadius, materials.at(0)));
    objects.push_back(std::make_shared<Sphere>(sphereCenter2, sphereRadius, materials.at(1)));

    this->width = image->getWidth();
    this->height = image->getHeight();

    // Create and initialize the light
    Vector3 lightDir = -(Vector3(-0.2f, -0.2f, 0.0f) - sphereCenter1); // Changed light direction
    lightDir = lightDir.Normalize();
    this->lightColor = Color(255,255,255,255,Image::pixel_format);
    this->lightDir = lightDir;

    // Create and initialize the camera
    Vector3 origin = Vector3(0.0f, 0.0f, 1.0f); // Move the camera back
    camera.setAspectRatio(static_cast<float>(width) / static_cast<float>(height));
    camera.setPosition(origin);
    camera.setPitch(0); // Adjust as needed
    camera.setYaw(0);   // Adjust as needed
}

Camera& Scene::getCamera() {
    return this->camera;
}

const std::vector<std::shared_ptr<Object>>& Scene::getObjects() const {
    return this->objects;
}
