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
            maleCharacterTexture.loadFromFile("Characters/Transparent.png");
            cout << ("Failed to load maleCharacter texture: " + malePath);
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

    mainCharacterSprite.setPosition(-120, 200);
    mainCharacterSprite.setScale(1, 1);
}

// Load textures from files and assign them to sprites
void LoadSprites::loadMenuScreen(const string& menuBackgroundPath) {
    //Checks if there is a file to load
    if (!menuBackgroundTexture.loadFromFile(menuBackgroundPath)) {
        menuBackgroundTexture.loadFromFile("Characters/Transparent.png");
        cout << ("Failed to load menuBackgroundPath texture: " + menuBackgroundPath);
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
        instructionBackgroundTexture.loadFromFile("Characters/Transparent.png");
        cout << ("Failed to load instruction background texture: " + insrtuctionBackgroundPath);
    }
    if (!menuScrollTexture.loadFromFile(menuScrollPath)) {
        menuScrollTexture.loadFromFile("Characters/Transparent.png");
        cout << ("Failed to load menuScroll texture: " + menuScrollPath);
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
        gameBackgroundTexture.loadFromFile("Characters/Transparent.png");
        cout << ("Failed to load gameBackground texture: " + gameBackgroundPath);
    }
    if (!gameScrollTexture.loadFromFile(gameScrollPath)) {
        gameBackgroundTexture.loadFromFile("Characters/Transparent.png");
        cout << ("Failed to load gamescroll texture: " + gameScrollPath);
    }

    //does god loading if it exists
    if (!godTexture.loadFromFile(godPath)) {
        godTexture.loadFromFile("Characters/Transparent.png");
        cout << ("Failed to load instruction background texture: " + godPath);
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
    godSprite.setScale(0.95f, 0.95f);
    FloatRect godBounds = godSprite.getGlobalBounds();
    godSprite.setPosition(WIN_WIDTH - godBounds.width * 0.7f, 160);

    //position scroll
    PositionScroll(gameScrollTexture.getSize().x, gameScrollTexture.getSize().y, gameScrollSprite);

}

void LoadSprites::loadDialogueScreen(const string& gameBackgroundPath, const string& godPath, const string& playerPath) {
    // Check and load game background if path is different and not empty
    if (!gameBackgroundPath.empty() && gameBackgroundPath != gameBackgroundPaths) {
        cout << gameBackgroundPath << endl;
        if (!gameBackgroundTexture.loadFromFile(gameBackgroundPath)) {
            cout << gameBackgroundPath + " didn't load" << endl;
            gameBackgroundTexture.loadFromFile("Characters/Transparent.png");
        }
        else {
            gameBackgroundPaths = gameBackgroundPath;
        }
        gameBackgroundSprite.setTexture(gameBackgroundTexture);
        fitBackground(WIN_WIDTH, WIN_HEIGHT, gameBackgroundTexture.getSize().x,
            gameBackgroundTexture.getSize().y, gameBackgroundSprite);
    }

    // Check and load god sprite if path is different and not empty
    if (!godPath.empty() && godPath != godPaths) {
        if (!godTexture.loadFromFile(godPath)) {
            cout << godPath + " didn't load" << endl;
            godTexture.loadFromFile("Characters/Transparent.png");
        }
        else {
            godPaths = godPath;
        }

        // Position god
        godSprite.setTexture(godTexture);
        godSprite.setScale(0.95f, 0.95f);
        FloatRect godBounds = godSprite.getGlobalBounds();
        godSprite.setPosition(WIN_WIDTH - godBounds.width * 0.7f, 160);
    }

    // Check and load player sprite if path is different and not empty
    if (!playerPath.empty() && playerPath != playerPaths) {
        if (!playerTexture.loadFromFile(playerPath)) {
            cout << playerPath + " didn't load" << endl;
            playerTexture.loadFromFile("Characters/Transparent.png");
        }
        else {
            playerPaths = playerPath;
        }
        mainCharacterSprite.setTexture(playerTexture);
    }

}

void LoadSprites::loadGameScroll(const string& gameScrollPath){
    if (!gameScrollTexture.loadFromFile(gameScrollPath)) {
        gameScrollTexture.loadFromFile("Characters/Transparent.png");
        cout << ("Failed to load Acessories / Scroll.png texture: ");
    }
    gameScrollSprite.setTexture(gameScrollTexture);
    //position scroll
    PositionScroll(gameScrollTexture.getSize().x, gameScrollTexture.getSize().y, gameScrollSprite);
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