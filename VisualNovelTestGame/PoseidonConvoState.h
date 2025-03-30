#pragma once
#include "State.h"

class PoseidonConvoState : public State {
private:
    sf::Texture backgroundTexture, godTexture, scrollTexture, mainCharacterTexture;
    sf::Sprite backgroundSprite, godSprite, scrollSprite, mainCharacterSprite;
    sf::Font font;
    sf::Text dialogText;
    sf::Vector2u windowSize;

public:
    PoseidonConvoState(sf::Vector2u windowSize);
    void load() override;
    void update() override;
    void draw(sf::RenderWindow& window) override;
};