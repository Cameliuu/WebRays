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
void updateSphere(Sphere sph)
{
    short id = sph.getId();
    for(auto& obj :App::instance->getScene()->getObjects())
    {
        if (obj->getId() == id)
        {
            obj = std::make_shared<Sphere>(sph);
        }
    }

    testobjs = App::instance->getScene()->getObjects();
}
bool getStartRender()
{
    return App::instance->startRendering;
}
bool getRenderingStarted()
{
    return App::instance->renderingStarted;
}
void switchRender()
{
    App::instance->startRendering = !App::instance->startRendering;

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
        .class_function("fromColorString", &Color::fromColorString)
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
        .property("id", &Object::getId)
        .function("hit", &Object::hit);
    class_<Sphere, base<Object>>("Sphere")
        .constructor<Vector3,float,Material&,short>()
        .smart_ptr<std::shared_ptr<Sphere>>("Sphere")
        .property("radius", &Sphere::getRadius)
        .property("center", &Sphere::getCenter, &Sphere::setCenter)
        .function("getTypeString", &Sphere::getTypeString);
    class_<Scene>("Scene")
        .smart_ptr<std::shared_ptr<Scene>>("Scene");
    class_<App>("App")
        .property("Scene", &App::getScene)
        .property("initialized", &App::isInitialized);

    register_vector<std::shared_ptr<Material>>("Materials");
    register_vector<std::shared_ptr<Object>>("Objects");

    function("getAppInstace",&getAppInstance, allow_raw_pointers());
    function("getObjs", &getObjs);
    function("printObjectsSize", &printObjectsSize);
    function("updateSphere",&updateSphere);
    function("getStartRender", &getStartRender);
    function("getRenderingStarted", &getRenderingStarted);
    function("switchRender", &switchRender);
}
EM_BOOL button_click_callback(int eventType, const EmscriptenMouseEvent* e, void* userData)
{
    emscripten_out("merge");
    return EM_TRUE;
}
int main() {

    App app = App();
    app.initialize(1280,720);
    testobjs = App::instance->getScene()->getObjects();
    emscripten_set_main_loop(App::instance->staticMainLoop,0,1);

    printObjectsSize();
    emscripten_set_click_callback("#myButton", nullptr, EM_TRUE, button_click_callback);
    return 0;
}
