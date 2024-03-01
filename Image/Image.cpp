

#include "Image.h"

void Image::initialize(int width, int height, SDL_Renderer *renderer) {
    this->width = width;
    this->height = height;

    pixels.resize(width*height);
    memset(pixels.data(), 0, pixels.size() * sizeof(Uint32));

    this->renderer = renderer;
}

void Image::display() {
            //Allocate pixel format
    SDL_PixelFormat* pixel_format = SDL_AllocFormat(SDL_PIXELFORMAT_ABGR8888);

    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, R_MASK, G_MASK, B_MASK, A_MASK);
    if (surface == NULL) {
        SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
        exit(1);
    }

    // Lock the surface for direct pixel access
    SDL_LockSurface(surface);

    // Set each pixel to a random color

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {

            float redRatio = static_cast<float>(x) / (width - 1);
            float greenRatio = static_cast<float>(y) / (height - 1);


            Uint8 red = static_cast<Uint8>(redRatio * 255);
            Uint8 green = static_cast<Uint8>(greenRatio * 255);
            Uint8 blue = 0;


            Color color(red, green, blue, 255,pixel_format);
            setPixel(surface, x, y, color.getMappedColor());
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

    Uint32 format;
    int access, w, h;
    SDL_QueryTexture(texture, &format, &access, &w, &h);
    std::cout << "Texture format: " << SDL_GetPixelFormatName(format) << std::endl;

    // Clear the renderer
    SDL_RenderClear(renderer);

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Update the screen
    SDL_RenderPresent(renderer);

    // Destroy the texture after rendering
    SDL_DestroyTexture(texture);

}
void Image::setPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
    Uint32* pixels = (Uint32*)surface->pixels;
    pixels[(y * surface->w) + x] = color;
}


