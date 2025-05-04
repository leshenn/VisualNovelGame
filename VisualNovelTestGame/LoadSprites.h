#pragma once  
#include <SFML/Graphics.hpp>  
#include <SFML/Window.hpp>  
#include <fstream>  
#include <iostream>  

using namespace std;
using namespace sf;

class LoadSprites {
public:
    // Window dimensions  
    const int WIN_WIDTH = 1280;
    const int WIN_HEIGHT = 720;

    // Load in all the textures  
    Texture menuBackgroundTexture;
    Texture gameBackgroundTexture;
    Texture instructionBackgroundTexture;
    Texture godTexture;
    Texture playerTexture;
    Texture gameScrollTexture;
    Texture menuScrollTexture;

    // Load in all the sprites  
    Sprite menuBackgroundSprite;
    Sprite instructionBackgroundSprite;
    Sprite gameBackgroundSprite;
    Sprite godSprite;
    Sprite playerSprite;
    Sprite gameScrollSprite;
    Sprite menuScrollSprite;

    // stores currently loaded sprite paths
    string godPaths;
    string playerPaths;
    string gameBackgroundPaths;


public:
    void loadMenuScreen(const string& menuBackgroundPath);

    void loadInstructionScreen(const string& insrtuctionBackgroundPath, const string& menuScrollPath);

    void loadGameScreen(const string& gameBackgroundPath, const string& godPath,
        const string& mainCharacterPath);

    void loadGameScroll(const string& gameScrollPath);

    void loadDialogueScreen(const string& gameBackgroundPath, const string& godPath, const string& playerPath);

    void fitBackground(float winWidth, float winHeight,
        float textureX, float textureY, Sprite& menuBackgroundSprite);

    void CenterMenuScroll(float textureX, float textureY, Sprite& scrollSprite);

    void PositionScroll(float textureX, float textureY, Sprite& mainCharacterSprite);

};