
#include "Color.h"

const Color Color::Red = Color(255, 0, 0, 255, Image::pixel_format);
const Color Color::Green = Color(0, 255, 0, 255, Image::pixel_format);
const Color Color::Black = Color(0, 0, 0, 255, Image::pixel_format);
const Color Color::Blue = Color(0, 0, 255, 255, Image::pixel_format);
Color::Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha, SDL_PixelFormat* format) {
    this->red_value = red;
    this->green_value = green;
    this->blue_value = blue;
    this->alpha_value = alpha;
    this->mapped_color = SDL_MapRGBA(format,red,green,blue,alpha);
}
std::ostream& operator<<(std::ostream& os, const Color& color) {
    os << "Red: " << static_cast<int>(color.getRedValue())
       << ", Green: " << static_cast<int>(color.getGreenValue())
       << ", Blue: " << static_cast<int>(color.getBlueValue());
    return os;
}

Uint32 Color::getMappedColor() const{
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

Uint8 Color::getRedValue() const {
    return this->red_value;
}

Uint8 Color::getBlueValue() const {
    return this->blue_value;
}

Uint8 Color::getGreenValue() const {
    return this->green_value;
}
