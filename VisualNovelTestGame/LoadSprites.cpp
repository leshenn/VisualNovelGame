#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "LoadSprites.h"

using namespace std;
using namespace sf;

// Load textures from files and assign them to sprites
void LoadSprites::loadMenuScreen(string& menuBackgroundPath) {
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

void LoadSprites::loadInstructionScreen(string& insrtuctionBackgroundPath, string& menuScrollPath) {
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
}

void LoadSprites::loadGameScreen(string& gameBackgroundPath,  string& godPath,
    string& mainCharacterPath, string& gameScrollPath) {
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
}

void LoadSprites::fitBackground(float winWidth, float winHeight, float textureX, float textureY, Sprite& menuBackgroundSprite) {
    float scaleX = static_cast<float>(winWidth) / textureX;
    float scaleY = static_cast<float>(winHeight) / textureY;
    menuBackgroundSprite.setScale(scaleX, scaleY);

}

