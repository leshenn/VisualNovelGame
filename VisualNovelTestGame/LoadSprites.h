#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class LoadSprites {
private:
	//Window dimetions
	const int WIN_WIDTH = 1080;
	const int WIN_HEIGHT = 720;

	//Load in all the textures
	Texture menuBackgroundTexture;
	Texture gameBackgroundTexture;
	Texture instructionBackgroundTexture;
	Texture godTexture;
	Texture mainCharacterTexture;
	Texture gameScrollTexture;
	Texture menuScrollTexture;

	//Load in all the sprites
	Sprite menuBackgroundSprite;
	Sprite instructionBackgroundSprite;
	Sprite gameBackgroundSprite;
	Sprite godSprite;
	Sprite mainCharacterSprite;
	Sprite gameScrollSprite;
	Sprite menuScrollSprite;

public:
	void loadMenuScreen(string& menuBackgroundPath);

	void loadInstructionScreen(string& insrtuctionBackgroundPath, string& menuScrollPath);

	void loadGameScreen(string& gameBackgroundPath, string& godPath,
						string& mainCharacterPath, string& gameScrollPath);
	
	void fitBackground(float winWidth, float winHeight, float textureX, float textureY, Sprite& menuBackgroundSprite);

};
