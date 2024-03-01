#include <iostream>
#include "App/App.h"
#include <emscripten.h>
int main() {
    App app = App();
    app.initialize(1280,720);
    emscripten_set_main_loop(App::instance->static_main_loop,0,1);
    return 0;
}
