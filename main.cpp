#include <iostream>
#include "App/App.h"
#include <emscripten.h>
#include <emscripten/html5.h>
#include "emscripten/bind.h"
using namespace emscripten;
std::vector<std::shared_ptr<Object>> testobjs;
App* getAppInstance()
{
    return App::instance;
}
std::vector<std::shared_ptr<Object>> getObjs()
{
    return testobjs;
}
void printObjectsSize()
{
    emscripten_log(EM_LOG_CONSOLE,"Size of objs: %d", testobjs.size());
}
EMSCRIPTEN_BINDINGS(color_module) {
    class_<Vector3>("Vector3")
       .constructor<float, float, float>()
       .property("x", &Vector3::GetX, &Vector3::SetX)
       .property("y", &Vector3::GetY, &Vector3::SetY)
       .property("z", &Vector3::GetZ, &Vector3::SetZ);
    class_<Color>("Color")
        .constructor<Uint8, Uint8, Uint8, Uint8>()
        .function("getColorString", &Color::getColorString)
        .property("red",&Color::getRedValue)
        .property("green",&Color::getGreenValue)
        .property("blue", &Color::getBlueValue)
        .property("alpha", &Color::getAlphaValue);
    class_<Material>("Material")
        .constructor<Color, Color, Color, float, float>()
        .smart_ptr<std::shared_ptr<Material>>("Material")
        .property("ambient", &Material::getAmbient, &Material::setAmbient)
        .property("diffuse", &Material::getDiffuse, &Material::setDiffuse)
        .property("specular", &Material::getSpecular, &Material::setSpecular)
        .property("shininess", &Material::getShininess, &Material::setShininess)
        .property("ambientStrength", &Material::getAmbientStrength, &Material::setAmbientStrength);
    class_<Object>("Object")
        .smart_ptr<std::shared_ptr<Object>>("Object")
        .property("material", &Object::getMaterial, &Object::setMaterial)
        .function("getId", &Object::getId)
        .function("hit", &Object::hit);
    class_<Sphere, base<Object>>("Sphere")
        .constructor<Vector3,float,Material&,short>()
        .smart_ptr<std::shared_ptr<Sphere>>("Sphere")
        .property("center", &Sphere::getCenter, &Sphere::setCenter);
    class_<Scene>("Scene")
        .smart_ptr<std::shared_ptr<Scene>>("Scene")
        .property("Objects",&Scene::getObjects);
    class_<App>("App")
        .property("Scene", &App::getScene);

    register_vector<std::shared_ptr<Material>>("Materials");
    register_vector<std::shared_ptr<Object>>("Objects");

    function("getAppInstace",&getAppInstance, allow_raw_pointers());
    function("getObjs", &getObjs);
    function("printObjectsSize", &printObjectsSize);
}

int main() {

    App app = App();
    app.initialize(1280,720);
    //emscripten_set_main_loop(App::instance->staticMainLoop,60,1);
    testobjs = App::instance->getScene()->getObjects();
    printObjectsSize();
    return 0;
}
