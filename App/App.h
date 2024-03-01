#ifndef APP_H
#define APP_H
#include <SDL.H>
#include <iostream>
#include <emscripten.h>
class App{
    public:
        bool initialize(int width,int height);
        void handle_events();
        void main_loop();
        void set_pixel(SDL_Surface* surface, int x, int y, Uint32 color);
        static void static_main_loop();
    static App* instance;

    private:
        int width, height;
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool isRunning = false;
        SDL_Texture* texture;

};

#endif