

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
        return true;
}

void App::main_loop() {
    handle_events();
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    if (surface == NULL) {
        SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
        exit(1);
    }

    // Lock the surface for direct pixel access
    SDL_LockSurface(surface);

    // Set each pixel to a random color
    Uint32 color;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Uint8 r = rand() % 256;
            Uint8 g = rand() % 256;
            Uint8 b = rand() % 256;
            color = SDL_MapRGB(surface->format, r, g, b);
            set_pixel(surface, x, y, color);
        }
    }

    // Unlock the surface
    SDL_UnlockSurface(surface);

    // Create a texture from the surface pixels
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); // we got a texture out of it, no need for the surface anymore

    if (texture == NULL) {
        SDL_Log("SDL_CreateTextureFromSurface() failed: %s", SDL_GetError());
        exit(1);
    }

    // Clear the renderer
    SDL_RenderClear(renderer);

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Update the screen
    SDL_RenderPresent(renderer);

    // Destroy the texture after rendering
    SDL_DestroyTexture(texture);

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

void App::set_pixel(SDL_Surface *surface, int x, int y, Uint32 color) {
    Uint32* pixels = (Uint32*)surface->pixels;
    pixels[(y * surface->w) + x] = color;
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
