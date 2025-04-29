#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <iostream>
#include "LoadSprites.h"

using namespace std;
using namespace sf;

void LoadSprites::loadCharacterOptions(const string& malePath, const string& femalePath) {
    // Only load textures if they haven't been loaded already
    if (maleCharacterTexture.getSize() == sf::Vector2u(0, 0)) {
        if (!maleCharacterTexture.loadFromFile(malePath)) {
            throw runtime_error("Failed to load male character texture.");
        }
    }

    // Default to male character
    isMaleCharacterSelected = true;
    updateMainCharacterDisplay();
}

void LoadSprites::selectCharacter(bool isMale) {
    if (isMaleCharacterSelected != isMale) {  // Only update if changed
        isMaleCharacterSelected = isMale;
        updateMainCharacterDisplay();
    }
}

void LoadSprites::updateMainCharacterDisplay() {
    mainCharacterSprite.setTexture(isMaleCharacterSelected ? maleCharacterTexture : femaleCharacterTexture);
    mainCharacterSprite.setPosition(0, 140);
    mainCharacterSprite.setScale(1, 1);
}

// Load textures from files and assign them to sprites
void LoadSprites::loadMenuScreen(const string& menuBackgroundPath) {
    //Checks if there is a file to load
    if (!menuBackgroundTexture.loadFromFile(menuBackgroundPath)) {
        throw runtime_error("Failed to load menu background texture.");
    }
    //Sets the textures
    menuBackgroundSprite.setTexture(menuBackgroundTexture);

    //Make the background fit the screen
    fitBackground(WIN_WIDTH, WIN_HEIGHT, menuBackgroundTexture.getSize().x,
        menuBackgroundTexture.getSize().y, menuBackgroundSprite);
    
}

void LoadSprites::loadInstructionScreen(const string& insrtuctionBackgroundPath, const string& menuScrollPath) {
    //Checks if there is a file to load
    if (!instructionBackgroundTexture.loadFromFile(insrtuctionBackgroundPath)) {
        throw runtime_error("Failed to load instruction background texture.");
    }
    if (!menuScrollTexture.loadFromFile(menuScrollPath)) {
        throw runtime_error("Failed to load menu scroll texture.");
    }

    //Sets the textures
    instructionBackgroundSprite.setTexture(instructionBackgroundTexture);
    menuScrollSprite.setTexture(menuScrollTexture);

    //Make the background fit the screen
    fitBackground(WIN_WIDTH, WIN_HEIGHT, instructionBackgroundTexture.getSize().x,
        instructionBackgroundTexture.getSize().y, instructionBackgroundSprite);

    //Make the scroll fit
    CenterMenuScroll(menuScrollTexture.getSize().x, menuScrollTexture.getSize().y, menuScrollSprite);
}

void LoadSprites::loadCharacterSelectionScreen(const string& backgroundPath) {
    // Load background
    if (!instructionBackgroundTexture.loadFromFile(backgroundPath)) {
        throw runtime_error("Failed to load instruction background texture.");
    }
    instructionBackgroundSprite.setTexture(instructionBackgroundTexture);

    fitBackground(WIN_WIDTH, WIN_HEIGHT,
        instructionBackgroundTexture.getSize().x,
        instructionBackgroundTexture.getSize().y,
        instructionBackgroundSprite);
}


void LoadSprites::loadGameScreen(const string& gameBackgroundPath, const string& godPath, const string& gameScrollPath) {
    //Checks if there is a file to load
    if (!gameBackgroundTexture.loadFromFile(gameBackgroundPath)) {
        throw runtime_error("Failed to load game background texture.");
    }
    if (!gameScrollTexture.loadFromFile(gameScrollPath)) {
        throw runtime_error("Failed to load game scroll texture.");
    }

    //does god loading if it exists
    if (!godTexture.loadFromFile(godPath)) {
        throw runtime_error("Failed to load god texture.");
    }
    else {
        godSprite.setTexture(godTexture);
    }

    //Sets the textures
    gameBackgroundSprite.setTexture(gameBackgroundTexture);

    gameScrollSprite.setTexture(gameScrollTexture);

    //Make the background fit the screen
    fitBackground(WIN_WIDTH, WIN_HEIGHT, gameBackgroundTexture.getSize().x,
        gameBackgroundTexture.getSize().y, gameBackgroundSprite);

    // The main character will use whatever texture was selected
    updateMainCharacterDisplay();

    //Position god
    godSprite.setPosition(730, 100);
    godSprite.setScale(1, 1);

    //position scroll
    PositionScroll(gameScrollTexture.getSize().x, gameScrollTexture.getSize().y, gameScrollSprite);

}

void LoadSprites::loadDialogueScreen(const string& gameBackgroundPath, const string& godPath, const string& playerPath) {
    //Checks if there is a file to load
    if (!gameBackgroundPath.empty()) {
        cout << gameBackgroundPath << endl;
        if (!gameBackgroundTexture.loadFromFile(gameBackgroundPath)) {
            throw runtime_error("Failed to load game background texture.");
        }
        gameBackgroundSprite.setTexture(gameBackgroundTexture);
        //Make the background fit the screen
        fitBackground(WIN_WIDTH, WIN_HEIGHT, gameBackgroundTexture.getSize().x,
            gameBackgroundTexture.getSize().y, gameBackgroundSprite);
    }

    if (!gameScrollTexture.loadFromFile("Acessories/Scroll.png")) {
        throw runtime_error("Failed to load game scroll texture.");
    }
    gameScrollSprite.setTexture(gameScrollTexture);
    //position scroll
    PositionScroll(gameScrollTexture.getSize().x, gameScrollTexture.getSize().y, gameScrollSprite);
    

    //does god loading if it exists
    if (!godPath.empty()) {
        if (!godTexture.loadFromFile(godPath)) {
            cout << godPath << endl;
            throw runtime_error("Failed to load god texture.");
        }
        else {
            godSprite.setTexture(godTexture);
            //Position god
            godSprite.setPosition(730, 100);
            godSprite.setScale(1, 1);
        }
    }

    //does player loading if it exists
    if (!playerPath.empty()) {
        if (!playerTexture.loadFromFile(playerPath)) {
            throw runtime_error("Failed to load player texture.");
        }
        else {
            mainCharacterSprite.setTexture(playerTexture);
        }
    }
}

void LoadSprites::fitBackground(float winWidth, float winHeight,
    float textureX, float textureY, Sprite& backgroundSprite) {
    // Calculate the scaling factors
    float scaleX = static_cast<float>(winWidth) / textureX;
    float scaleY = static_cast<float>(winHeight) / textureY;

    // Set the sprite's scale
    backgroundSprite.setScale(scaleX, scaleY);

    // Optionally, center the sprite if you want the background to be centered
    backgroundSprite.setPosition(0, 0);  // Aligns the background to the top-left corner
}

void LoadSprites::CenterMenuScroll(float textureX, float textureY, Sprite& scrollSprite) {
    // Calculate the scaling factors
    float scaleX = static_cast<float>(852) / textureX;
    float scaleY = static_cast<float>(480) / textureY;

    // Set the sprite's scale
    scrollSprite.setScale(scaleX, scaleY);

    // Optionally, center the sprite if you want the background to be centered
    scrollSprite.setPosition(214, 120);  // Aligns the background to the center
}

void LoadSprites::PositionScroll(float textureX, float textureY, Sprite& scrollSprite) {
    // Calculate the scaling factors
    float scaleX = static_cast<float>(1250) / textureX;
    float scaleY = static_cast<float>(380) / textureY;

    // Set the sprite's scale
    scrollSprite.setScale(scaleX, scaleY);
    scrollSprite.setPosition(20, 350);
}




