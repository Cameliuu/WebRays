

#include "App.h"
void* renderThread(void* arg) {
    Image* image = static_cast<Image*>(arg);

    // Perform rendering calculations
    App::instance->renderingStarted = true;
    App::instance->getScene().render(image);

    App::instance->renderingDone = true;

    return nullptr;
}
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
        scene.initialize(&image);
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


void App::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        else if(event.type == SDL_KEYDOWN) {
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


