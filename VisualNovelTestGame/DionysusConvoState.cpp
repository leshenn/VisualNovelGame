#include "DionysusConvoState.h"

DionysusConvoState::DionysusConvoState(sf::Vector2u windowSize) : windowSize(windowSize) {}

void DionysusConvoState::load() {
    // Load main character
    mainCharacterTexture.loadFromFile("Characters/MainCharacter.png");
    mainCharacterSprite.setTexture(mainCharacterTexture);
    mainCharacterSprite.setPosition(5, 220);

    // Load background
    backgroundTexture.loadFromFile("Backgrounds/DionysusBackground.jpg");
    sf::Vector2u textureSize = backgroundTexture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);
    backgroundSprite.setTexture(backgroundTexture);

    // Load Hades
    godTexture.loadFromFile("Characters/Dionysus.png");
    godSprite.setTexture(godTexture);
    godSprite.setPosition(600, 220);

    // Load scroll
    scrollTexture.loadFromFile("scroll.png");
    scrollSprite.setTexture(scrollTexture);
    scrollSprite.setScale(0.36f, 0.36f);
    scrollSprite.setPosition(155, 300);

    // Set dialog text
    font.loadFromFile("Robot_Font.otf");
    dialogText.setFont(font);
    dialogText.setString("I am Dionysus, and this is my vineyard.");
    dialogText.setCharacterSize(24);
    dialogText.setFillColor(sf::Color::Black);
    dialogText.setPosition(300, 375);
}

void DionysusConvoState::update() {
    // Handle updates (if needed)
}

void DionysusConvoState::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(scrollSprite);
    window.draw(godSprite);
    window.draw(mainCharacterSprite);
    window.draw(dialogText);
}