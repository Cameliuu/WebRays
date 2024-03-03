
#include "Color.h"

Color::Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha, SDL_PixelFormat* format) {
    this->red_value = red;
    this->green_value = green;
    this->blue_value = blue;
    this->alpha_value = alpha;
    this->mapped_color = SDL_MapRGBA(format,red,green,blue,alpha);
}

Uint32 Color::getMappedColor() {
    return this->mapped_color;
}

Color::Color() {

}

void Color::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha, SDL_PixelFormat *format) {
    this->red_value = red;
    this->green_value = green;
    this->blue_value = blue;
    this->alpha_value = alpha;
    this->mapped_color = SDL_MapRGBA(format,red,green,blue,alpha);
}
