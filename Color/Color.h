#ifndef COLOR_H
#define COLOR_H
#include <SDL.H>
#include "../Image/Image.h"

class Color{
    public:
    static const Color Red;
    static const Color Black;
    static const Color Blue;

    Color();
    Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha, SDL_PixelFormat* format);
    Uint32 getMappedColor() const;
    void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha, SDL_PixelFormat* format);

    Uint8 getRedValue() const;
    Uint8 getBlueValue() const;
    Uint8 getGreenValue() const;

    friend std::ostream& operator<<(std::ostream& os, const Color& color);
    private:
    Uint8 red_value,green_value,blue_value,alpha_value;
    Uint32 mapped_color;
};
#endif
