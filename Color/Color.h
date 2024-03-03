#ifndef COLOR_H
#define COLOR_H
#include <SDL.H>


class Color{
    public:
    Color();
    Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha, SDL_PixelFormat* format);
    Uint32 getMappedColor();
    void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha, SDL_PixelFormat* format);
    private:
    Uint8 red_value,green_value,blue_value,alpha_value;
    Uint32 mapped_color;
};
#endif
