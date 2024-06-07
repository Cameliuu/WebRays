#include <iostream>
#include "App/App.h"
#include <emscripten.h>
#include <emscripten/html5.h>

EM_BOOL keypress_callback(int eventType, const EmscriptenKeyboardEvent *e, void *userData){
        Camera& camera = App::instance->getScene().getCamera();
        Vector3 currentPos = camera.getPosition();
        if((strcmp(e->key,"w")==0))
        {

            camera.setPoisitionZ(currentPos.GetZ()-0.1f);
        }
        else if((strcmp(e->key,"s")==0))
        {
            camera.setPoisitionZ(currentPos.GetZ()+0.1f);
        }
    return EM_TRUE;
}

int main() {

    App app = App();
    app.initialize(1280,720);
    //emscripten_set_main_loop(App::instance->staticMainLoop,60,1);
    return 0;
}
