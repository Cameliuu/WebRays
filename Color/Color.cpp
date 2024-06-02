#include "Color.h"

// Define static member variables
const Color Color::White = Color(255, 255, 255, 255);
const Color Color::Red = Color(255, 0, 0, 255);
const Color Color::Green = Color(0, 255, 0, 255);
const Color Color::Black = Color(0, 0, 0, 255);
const Color Color::Blue = Color(0, 0, 255, 255);
const Color Color::Gray = Color(192, 192, 192, 255);

// Parameterized constructor using initializer list
Color::Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
    : red_value(red), green_value(green), blue_value(blue), alpha_value(alpha) {
    this->mapped_color = SDL_MapRGBA(Image::pixel_format, red, green, blue, alpha);
}

// Default constructor
Color::Color() : red_value(0), green_value(0), blue_value(0), alpha_value(0), mapped_color(0) {}

// Setter method
void Color::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    this->red_value = red;
    this->green_value = green;
    this->blue_value = blue;
    this->alpha_value = alpha;
    this->mapped_color = SDL_MapRGBA(Image::pixel_format, red, green, blue, alpha);
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
Uint8 Color::getAlphaValue() const {
    return this->alpha_value;
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
    return Color(newRed, newGreen, newBlue, newAlpha);
}

// Template for division operator
template <typename T>
Color Color::divide(T value) const {
    Uint8 newRed = static_cast<Uint8>(red_value / value);
    Uint8 newGreen = static_cast<Uint8>(green_value / value);
    Uint8 newBlue = static_cast<Uint8>(blue_value / value);
    Uint8 newAlpha = static_cast<Uint8>(alpha_value / value);
    return Color(newRed, newGreen, newBlue, newAlpha);
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
    Uint8 newRed = std::min(static_cast<int>(red_value) + static_cast<int>(other.red_value),255);
    Uint8 newGreen = std::min(static_cast<int>(green_value) + static_cast<int>(other.green_value),255);
    Uint8 newBlue = std::min(static_cast<int>(blue_value) + static_cast<int>(other.blue_value),255);
    Uint8 newAlpha = std::min(static_cast<int>(alpha_value) + static_cast<int>(other.alpha_value),255);
    return Color(newRed, newGreen, newBlue, newAlpha);
}

Color Color::operator*(const Color& other) const
{

    // Normalize the colors to the 0.0-1.0 range
    float r1 = red_value / 255.0f;
    float g1 = green_value / 255.0f;
    float b1 = blue_value / 255.0f;
    float a1 = alpha_value / 255.0f;

    float r2 = other.getRedValue() / 255.0f;
    float g2 = other.getGreenValue() / 255.0f;
    float b2 = other.getBlueValue() / 255.0f;
    float a2 = other.getAlphaValue() / 255.0f;

    // Multiply the normalized values
    float rResult = r1 * r2;
    float gResult = g1 * g2;
    float bResult = b1 * b2;
    float aResult = a1 * a2;

    // Convert back to the 0-255 range
    unsigned char newRed = static_cast<unsigned char>(rResult * 255);
    unsigned char newGreen = static_cast<unsigned char>(gResult * 255);
    unsigned char newBlue = static_cast<unsigned char>(bResult * 255);
    unsigned char newAlpha = static_cast<unsigned char>(aResult * 255);

    return Color(newRed, newGreen, newBlue, alpha_value);

}

Color Color::addWithoutClamping(const Color& other) const
{
    Uint8 newRed = static_cast<int>(red_value) + static_cast<int>(other.red_value);
    Uint8 newGreen = static_cast<int>(green_value) + static_cast<int>(other.green_value);
    Uint8 newBlue = static_cast<int>(blue_value) + static_cast<int>(other.blue_value);
    Uint8 newAlpha = static_cast<int>(alpha_value) + static_cast<int>(other.alpha_value);
    return Color(newRed, newGreen, newBlue, newAlpha);
}


// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& os, const Color& color) {
    os << "Red: " << static_cast<int>(color.getRedValue())
       << ", Green: " << static_cast<int>(color.getGreenValue())
       << ", Blue: " << static_cast<int>(color.getBlueValue())
       << ", Alpha: " << static_cast<int>(color.alpha_value);
    return os;
}
