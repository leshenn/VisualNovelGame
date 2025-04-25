#include "ProgressBar.h"
#include <iostream> // For debugging purposes

ProgressBar::ProgressBar(RenderWindow& window) : window(window), currentWidth(0.f) {
    maxWidth = 226.5f;

    Outline.setFillColor(Color::White);
    Outline.setSize(Vector2f(maxWidth, 12.f));
    //.setOutlineThickness(3);
    Outline.setOutlineColor(Color::Black);
    Outline.setPosition(19.f, 25.f);

    Bar.setFillColor(Color::Green);
    Bar.setSize(Vector2f(0, 15.f));  // Starts at 0 width
    Bar.setPosition(19.f, 25.f);
}

void ProgressBar::update() {
    currentWidth += 1.5;
	std::cout << currentWidth << std::endl; // Debugging line to check currentWidth
    //  it doesn’t go beyond the bar
    if (currentWidth > maxWidth) currentWidth = maxWidth;

    Bar.setSize(Vector2f(currentWidth, 12));
    
}

void ProgressBar::draw() {
    window.draw(Outline);
    window.draw(Bar);
}

