#include "Color.h"

// Define static member variables
const Color Color::Red = Color(255, 0, 0, 255, Image::pixel_format);
const Color Color::Green = Color(0, 255, 0, 255, Image::pixel_format);
const Color Color::Black = Color(0, 0, 0, 255, Image::pixel_format);
const Color Color::Blue = Color(0, 0, 255, 255, Image::pixel_format);

// Parameterized constructor using initializer list
Color::Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha, SDL_PixelFormat* format)
    : red_value(red), green_value(green), blue_value(blue), alpha_value(alpha) {
    this->mapped_color = SDL_MapRGBA(format, red, green, blue, alpha);
}

// Default constructor
Color::Color() : red_value(0), green_value(0), blue_value(0), alpha_value(0), mapped_color(0) {}

// Setter method
void Color::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha, SDL_PixelFormat *format) {
    this->red_value = red;
    this->green_value = green;
    this->blue_value = blue;
    this->alpha_value = alpha;
    this->mapped_color = SDL_MapRGBA(format, red, green, blue, alpha);
}

// Getter methods
Uint8 Color::getRedValue() const {
    return this->red_value;
}

Uint8 Color::getGreenValue() const {
    return this->green_value;
}

Uint8 Color::getBlueValue() const {
    return this->blue_value;
}

Uint32 Color::getMappedColor() const {
    return this->mapped_color;
}

// Method to get color string
std::string Color::getColorString() const {
    return "RGBA(" + std::to_string(this->red_value) + ", " +
           std::to_string(this->green_value) + ", " +
           std::to_string(this->blue_value) + ", " +
           std::to_string(this->alpha_value) + ")";
}

// Overloaded multiplication operator
Color Color::operator*(float value)  {
    Uint8 newRed = static_cast<Uint8>(red_value * value);
    Uint8 newGreen = static_cast<Uint8>(green_value * value);
    Uint8 newBlue = static_cast<Uint8>(blue_value * value);
    Uint8 newAlpha = static_cast<Uint8>(alpha_value * value);
    return Color(newRed, newGreen, newBlue, newAlpha, Image::pixel_format);
}

// Template for division operator
template <typename T>
Color Color::divide(T value) const {
    Uint8 newRed = static_cast<Uint8>(red_value / value);
    Uint8 newGreen = static_cast<Uint8>(green_value / value);
    Uint8 newBlue = static_cast<Uint8>(blue_value / value);
    Uint8 newAlpha = static_cast<Uint8>(alpha_value / value);
    return Color(newRed, newGreen, newBlue, newAlpha, Image::pixel_format);
}

// Overloaded division operators
Color Color::operator/(float value) {
    return this->divide(value);
}

Color Color::operator/(double value) {
    return this->divide(value);
}

// Overloaded addition operator
Color Color::operator+(const Color& other) const {
    Uint8 newRed = static_cast<int>(red_value) + static_cast<int>(other.red_value);
    Uint8 newGreen = static_cast<int>(green_value) + static_cast<int>(other.green_value);
    Uint8 newBlue = static_cast<int>(blue_value) + static_cast<int>(other.blue_value);
    Uint8 newAlpha = static_cast<int>(alpha_value) + static_cast<int>(other.alpha_value);
    return Color(newRed, newGreen, newBlue, newAlpha, Image::pixel_format);
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& os, const Color& color) {
    os << "Red: " << static_cast<int>(color.getRedValue())
       << ", Green: " << static_cast<int>(color.getGreenValue())
       << ", Blue: " << static_cast<int>(color.getBlueValue())
       << ", Alpha: " << static_cast<int>(color.alpha_value);
    return os;
}
