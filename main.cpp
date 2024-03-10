#include <iostream>
#include "App/App.h"
#include <emscripten.h>
#include <emscripten/html5.h>

EM_BOOL keypress_callback(int eventType, const EmscriptenKeyboardEvent *e, void *userData){
    emscripten_out("aasdad");
    return EM_TRUE;
}
int main() {
    App app = App();
    app.initialize(1280,720)
    emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, 1, keypress_callback);
    emscripten_set_main_loop(App::instance->staticMainLoop,60,1);
    return 0;
}
