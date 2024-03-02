#ifndef APP_H
#define APP_H
#include <SDL.H>
#include <iostream>
#include <emscripten.h>
#include "../Image/Image.h"
#include "../Scene/scene.h"
class App{
    public:
        bool initialize(int width,int height);
        void handleEvents();
        void mainLoop();

        static void staticMainLoop();
    static App* instance;

    private:
        Image image;
        Scene scene;
        int width, height;
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool isRunning = false;
        SDL_Texture* texture;

};

#endif