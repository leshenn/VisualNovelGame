#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"
#include "GameState.h"

using namespace std;
using namespace sf;

class ButtonLayout
{
public:
	ButtonLayout(RenderWindow& window, Font& font);
	void loadPlayButton();
	void loadWorldButtons();
	void loadNextButton();
	void loadQuizButtons(GameState& currentState);

private:
	RenderWindow& window;
	Font font;

};

