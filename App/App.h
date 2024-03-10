#ifndef APP_H
#define APP_H
#include <SDL.H>
#include <iostream>
#include <emscripten.h>
#include "../Image/Image.h"
#include "../Scene/scene.h"
#include <atomic>
class App{
    public:
        bool initialize(int width,int height);
        void handleEvents();
        void mainLoop();
        Scene& getScene();
        static void staticMainLoop();
        std::atomic<bool> renderingDone;
        std::atomic<bool> renderingStarted;
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