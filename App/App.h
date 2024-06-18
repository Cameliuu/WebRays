#ifndef APP_H
#define APP_H
#include <SDL.H>
#include <iostream>
#include <emscripten.h>
#include "../Image/Image.h"
#include "../Scene/scene.h"
#include <atomic>
#include <fstream>
#include <sstream>
class App{
    public:
        bool initialize(int width,int height);
        void handleEvents();
        void mainLoop();
        std::shared_ptr<Scene> getScene() const;
        static void staticMainLoop();
        std::atomic<bool> startRendering;
        std::atomic<bool> renderingDone;
        std::atomic<bool> renderingStarted;
        bool isInitialized() const;
        static std::string ReadAllText(std::string path);
        static std::string configFile;
        static std::atomic<bool> loadingDone;
    static App* instance;

    private:
        Image image;
        bool initialized;
        std::shared_ptr<Scene> scene;
        int width, height;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_GLContext context;
        bool isRunning = false;
        SDL_Texture* texture;

};

#endif