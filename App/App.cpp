

#include "App.h"

void* renderThread(void* arg) {


    Image* image = static_cast<Image*>(arg);

    // Perform rendering calculations
    App::instance->renderingStarted = true;
    App::instance->getScene()->render(image);

    App::instance->renderingDone = true;

    return nullptr;
}


App* App::instance = nullptr;

std::string App::configFile = "materials.json";
std::atomic<bool> App::loadingDone = false;
bool App::initialize(int width, int height) {
        startRendering = false;
        if(SDL_Init(SDL_INIT_VIDEO)!=0)
        {
            std::cout << "[ ! ] SDL initialization failed\n";
            return false;
        }
        SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#canvas");
        if(SDL_CreateWindowAndRenderer(width, height,0,&window,&renderer)!=0)
        {
            std::cout << "[ ! ] Failed to create window and renderer\n";
        }
        context = SDL_GL_CreateContext(window);
        App::instance = this;
        scene = std::make_shared<Scene>();
        this->width = width;
        this->height = height;
        isRunning = true;
        image.initialize(1280,720,this->renderer);
        scene->initialize(&image);





        this->initialized = true;
        return true;
}

void App::mainLoop() {



    if (!renderingStarted && startRendering) {
        // Start the rendering thread only if it hasn't been started yet
        pthread_t renderThreadId;
        int rc = pthread_create(&renderThreadId, NULL, renderThread, &image);
        if (rc) {
            std::cerr << "Error: Unable to create thread," << rc << std::endl;
            exit(-1);
        }

    }

    // Check if rendering is done
    if (renderingDone) {
        emscripten_out("rendering done");
        // Reset the flag for the next rendering
        renderingDone = false;

        // Display the rendered image
        image.display();

        // Reset renderingStarted if you want to render again
        renderingStarted = false;
        startRendering = false;

    }

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



void App::staticMainLoop() {
    App::instance->mainLoop();
}

bool App::isInitialized() const
{
    return this->initialized;
}

std::string App::ReadAllText(std::string filePath)
{
    std::ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        emscripten_log(EM_LOG_CONSOLE, "Unable to open file: %s", filePath.c_str());
        throw std::runtime_error("Unable to open file");
    }

    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
    fileStream.close();
}


void App::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }

        }

    }


std::shared_ptr<Scene> App::getScene() const{
    return this->scene;
}


