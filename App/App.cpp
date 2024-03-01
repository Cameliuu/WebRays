

#include "App.h"
App* App::instance = nullptr;
bool App::initialize(int width, int height) {
        if(SDL_Init(SDL_INIT_VIDEO)!=0)
        {
            std::cout << "[ ! ] SDL initialization failed\n";
            return false;
        }
        if(SDL_CreateWindowAndRenderer(width, height,0,&window,&renderer)!=0)
        {
            std::cout << "[ ! ] Failed to create window and renderer\n";
        }
        App::instance = this;
        this->width = width;
        this->height = height;
        isRunning = true;
        image.initialize(1280,720,this->renderer);
        return true;
}

void App::main_loop() {
    handle_events();

    image.display();

    if (!isRunning) {
        // Clean up and exit the loop
        emscripten_cancel_main_loop();
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
}


void App::static_main_loop() {
    App::instance->main_loop();
}


void App::handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }

    }
}
