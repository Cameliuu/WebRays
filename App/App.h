#ifndef APP_H
#define APP_H
#include <SDL.H>
#include <iostream>
#include <emscripten.h>
#include "../Image/Image.h"

class App{
    public:
        bool initialize(int width,int height);
        void handle_events();
        void main_loop();

        static void static_main_loop();
    static App* instance;

    private:
        Image image;
        int width, height;
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool isRunning = false;
        SDL_Texture* texture;

};

#endif