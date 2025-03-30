#include "Button.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

Button::Button() {
    button.setSize({ 100, 50 });  // Default size
    button.setFillColor(sf::Color::White); // Default color
}

Button::Button(string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
    text.setString(t);
    text.setFillColor(textColor);
    text.setCharacterSize(charSize);

    button.setSize(size);
    button.setFillColor(bgColor);
}

void Button::setFont(sf::Font& font) {
    text.setFont(font);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
    textRect.top + textRect.height / 2.0f);
}

void Button::setBackColor(sf::Color color) {
    button.setFillColor(color);
}

void Button::setTextColor(sf::Color color) {
    text.setFillColor(color);
}

void Button::setPosition(sf::Vector2f pos) {
    button.setPosition(pos);

    float xPos = pos.x + (button.getSize().x / 2) - (text.getLocalBounds().width / 2);
    float yPos = pos.y + (button.getSize().y / 2) - (text.getLocalBounds().height / 2);
    text.setPosition({ xPos, yPos });
}

void Button::drawTo(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window); // Get integer position
    float mouseX = static_cast<float>(mousePos.x);
    float mouseY = static_cast<float>(mousePos.y);

    float btnPosX = button.getPosition().x;
    float btnPosY = button.getPosition().y;

    float btnWidth = button.getSize().x;
    float btnHeight = button.getSize().y;

    return (mouseX > btnPosX && mouseX < btnPosX + btnWidth &&
        mouseY > btnPosY && mouseY < btnPosY + btnHeight);
}

