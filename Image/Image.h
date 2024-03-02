#ifndef IMAGE_H
#define IMAGE_H
#include <SDL.H>
#include <vector>
#include <iostream>
#include "../Color/color.h"
#include <string.h>

//COLORS MASKS
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
const uint32_t R_MASK = 0xff000000;
const uint32_t G_MASK = 0x00ff0000;
const uint32_t B_MASK = 0x0000ff00;
const uint32_t A_MASK = 0x000000ff;
#else
const uint32_t R_MASK = 0x000000ff;
    const uint32_t G_MASK = 0x0000ff00;
    const uint32_t B_MASK = 0x00ff0000;
    const uint32_t A_MASK = 0xff000000;
#endif



class Image{
    public:
    void initialize(int width, int height,SDL_Renderer* renderer);
    void display();
    void setPixel(int x, int y, Uint32 color);
    int getWidth();
    int getHeight();
    static SDL_PixelFormat* pixel_format;
private:
    int width,height;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    std::vector<Uint32> pixels;

};
#endif IMAGE_H

