#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"

using namespace std;
using namespace sf;

class ButtonLayout
{
public:
	ButtonLayout(RenderWindow& window, Font& font);
	void loadPlayButton();
	void loadWorldButtons();


private:
	RenderWindow& window;
	Font font;

};

