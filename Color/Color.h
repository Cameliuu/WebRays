#ifndef COLOR_H
#define COLOR_H

#include <SDL.h>
#include <string>
#include <algorithm>
#include <iostream>
#include "../Image/Image.h"
#include "../Json/json.hpp"

class Color {
public:
    // Static predefined colors
    static const Color Red;
    static const Color Green;
    static const Color Black;
    static const Color Blue;
    static const Color White;
    static const Color Gray;
    // Constructors
    Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
    Color();

    // Getter methods
    Uint8 getRedValue() const;
    Uint8 getGreenValue() const;
    Uint8 getBlueValue() const;
    Uint8 getAlphaValue() const;
    Uint32 getMappedColor() const;

    // Method to get color string
    std::string getColorString() const;

    // Setter method
    void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

    // Overloaded operators
    Color operator*(float value);

    template <typename T>
    Color divide(T value) const;

    Color operator/(float value);
    Color operator/(double value);
    Color operator+(const Color& other) const;
    Color operator*(const Color& other) const;

    //Methos
    Color addWithoutClamping(const Color& other) const;
    // Overloaded stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Color& color);

    void from_json(const nlohmann::json& j, Color& obj)
    {
        j.at("red").get_to(obj.red_value);
        j.at("green").get_to(obj.green_value);
        j.at("blue").get_to(obj.blue_value);
        j.at("alpha").get_to(obj.alpha_value);

    }

private:
    Uint8 red_value;
    Uint8 green_value;
    Uint8 blue_value;
    Uint8 alpha_value;
    Uint32 mapped_color;
};

#endif // COLOR_H
