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

#include "../Config/Config.h"

class App{
    public:
        bool initialize();
        void handleEvents();
        void mainLoop();
        std::shared_ptr<Scene> getScene() const;
        static void staticMainLoop();
        std::shared_ptr<Config> getConfig() const;
        std::atomic<bool> startRendering;
        std::atomic<bool> renderingDone;
        std::atomic<bool> renderingStarted;
        void setConfig(Config& config);
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
        std::shared_ptr<Config> config;
        bool isRunning = false;
        SDL_Texture* texture;

};

#endif