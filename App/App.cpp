

#include "App.h"

void* renderThread(void* arg) {
    Image* image = static_cast<Image*>(arg);

    // Perform rendering calculations
    App::instance->renderingStarted = true;
    App::instance->getScene().render(image);

    App::instance->renderingDone = true;

    return nullptr;
}
EM_BOOL checkbox_callback(
    int eventType,
    const EmscriptenMouseEvent *mouseEvent,
    void *userData)
{
    if (eventType == EMSCRIPTEN_EVENT_CLICK) {
        // Access the App instance
        App* appInstance = static_cast<App*>(userData);

        // Access the Scene instance from the App instance
        Scene& scene = appInstance->getScene();

        // Access the objects vector from the Scene instance
        const std::vector<std::shared_ptr<Object>>& objects = scene.getObjects();

        // Iterate over the objects vector and do something
        for (const auto& object : objects) {
            emscripten_out("merge");
        }
    }

    return 0;
}

App* App::instance = nullptr;
std::string App::json = App::ReadAllText("materials.json");
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
        context = SDL_GL_CreateContext(window);
        App::instance = this;
        this->width = width;
        this->height = height;
        isRunning = true;
        image.initialize(1280,720,this->renderer);
        scene.initialize(&image);





    emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW,
    this,
    1,
    checkbox_callback
);

        return true;
}

void App::mainLoop() {



    if (!renderingStarted) {
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
        // Reset the flag for the next rendering
        renderingDone = false;

        // Display the rendered image
        image.display();

        // Reset renderingStarted if you want to render again
        renderingStarted = false;
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
}


void App::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        else if(event.type == SDL_KEYDOWN) {
            emscripten_out("Intra pe keydown");
            Camera& camera = App::instance->getScene().getCamera();
            Vector3 currentPos = camera.getPosition();
            switch (event.key.keysym.sym) {
                case SDLK_a: // Left
                    camera.setPoisitionX(currentPos.GetX()-0.1f);
                    break;
                case SDLK_d: // Right
                    camera.setPoisitionX(currentPos.GetX()+0.1f);
                    break;
                case SDLK_w: // Up
                    camera.setPoisitionZ(currentPos.GetZ()-0.1f);
                    break;
                case SDLK_s: // Down
                    camera.setPoisitionZ(currentPos.GetZ()+0.1f);
                    break;
                case SDLK_SPACE:
                    if (event.key.keysym.mod & KMOD_SHIFT) {
                        // Shift is down, so move camera up
                        camera.setPoisitionY(currentPos.GetY() + 0.1f);
                    } else {
                        // Shift is not down, move camera down
                        camera.setPoisitionY(currentPos.GetY() - 0.1f);
                    }
                    break;


            }
        }

    }
}

Scene& App::getScene() {
    return this->scene;
}


