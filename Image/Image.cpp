

#include "Image.h"
SDL_PixelFormat* Image::pixel_format = SDL_AllocFormat(SDL_PIXELFORMAT_ABGR8888);
void Image::initialize(int width, int height, SDL_Renderer *renderer) {
    this->width = width;
    this->height = height;

    pixels.resize(width*height);
    memset(pixels.data(), 0, pixels.size() * sizeof(Uint32));

    this->renderer = renderer;
}

void Image::display() {
            //Allocate pixel format


    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, R_MASK, G_MASK, B_MASK, A_MASK);
    if (surface == NULL) {
        SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
        exit(1);
    }

    // Lock the surface for direct pixel access
    SDL_LockSurface(surface);

    memcpy(surface->pixels,pixels.data(),pixels.size() * sizeof(Uint32));




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

}


void Image::setPixel(int x, int y, Uint32 color) {
    this->pixels[(y * width) + x] = color;
}

int Image::getWidth() {
    return this->width;
}

int Image::getHeight() {
    return this->height;
}





