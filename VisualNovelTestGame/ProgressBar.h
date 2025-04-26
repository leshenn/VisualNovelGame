#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <SFML/Graphics.hpp>
using namespace sf;

class ProgressBar {
private:
    RenderWindow& window;
    RectangleShape Outline;
    RectangleShape Bar;
    float maxWidth;
    float currentWidth;

public:
    ProgressBar(RenderWindow& window);
    void update();
    void draw();
};

#endif

