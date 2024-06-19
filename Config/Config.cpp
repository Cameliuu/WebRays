#include "Config.h"

// Getters
int Config::getHeight() const {
    return height;
}

int Config::getWidth() const {
    return width;
}

Color Config::getColor() const {
    return color;
}

int Config::getAASamplings() const {
    return aaSamplings;
}

// Setters
void Config::setHeight(int height) {
    this->height = height;
}

void Config::setWidth(int width) {
    this->width = width;
}

void Config::setAASamplings(int aaSamplings)
{
    this->aaSamplings = aaSamplings;
}

