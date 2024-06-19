#include <memory>
#include "../Color/Color.h"

#ifndef CONFIG_H
#define CONFIG_H

class Config {
public:
    Config(int width, int height, Color color, int samplings) : height(height), width(width), color(color), aaSamplings(samplings){}
    // Getters
    int getHeight() const;
    int getWidth() const;
    Color getColor() const;
    int getAASamplings() const;

    // Setters
    void setHeight(int height);
    void setWidth(int width);

    void setAASamplings(int aaSamplings);

private:
    int height, width;
    Color color;
    int aaSamplings;
};

#endif // CONFIG_H
