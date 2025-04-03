#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class LoadSprites {
private:
	//Load in all the textures
	Texture gameBackgroundTexture;
	Texture menuBackgroundTexture;
	Texture godTexture;
	Texture mainCharacterTexture;
	Texture scrollTexture;

	//Load in all the sprites
	Sprite backgroundSprite;
	Sprite godSprite;
	Sprite mainCharacterSprite;
	Sprite scrollSprite;

public:
};