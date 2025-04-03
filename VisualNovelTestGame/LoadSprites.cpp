#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "LoadSprites.h"

using namespace std;
using namespace sf;

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

void LoadSprites::loadGameScreen(const string& gameBackgroundPath, const string& godPath,
    const string& mainCharacterPath,const string& gameScrollPath) {
    //Checks if there is a file to load
    if (!gameBackgroundTexture.loadFromFile(gameBackgroundPath)) {
        throw runtime_error("Failed to load game background texture.");
    }
    if (!godTexture.loadFromFile(godPath)) {
        throw runtime_error("Failed to load god texture.");
    }
    if (!mainCharacterTexture.loadFromFile(mainCharacterPath)) {
        throw runtime_error("Failed to load main character texture.");
    }
    if (!gameScrollTexture.loadFromFile(gameScrollPath)) {
        throw runtime_error("Failed to load game scroll texture.");
    }

    //Sets the textures
    gameBackgroundSprite.setTexture(gameBackgroundTexture);
    godSprite.setTexture(godTexture);
    mainCharacterSprite.setTexture(mainCharacterTexture);
    gameScrollSprite.setTexture(gameScrollTexture);

    //Make the background fit the screen
    fitBackground(WIN_WIDTH, WIN_HEIGHT, gameBackgroundTexture.getSize().x,
        gameBackgroundTexture.getSize().y, gameBackgroundSprite);
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
    float scaleX = static_cast<float>(426) / textureX;
    float scaleY = static_cast<float>(240) / textureY;

    // Set the sprite's scale
    scrollSprite.setScale(scaleX, scaleY);

    // Optionally, center the sprite if you want the background to be centered
    scrollSprite.setPosition(0, 0);  // Aligns the background to the top-left corner
}

