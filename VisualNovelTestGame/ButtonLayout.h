#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"

using namespace std;
using namespace sf;

class ButtonLayout
{
public:

	// Initialise window and font
	ButtonLayout(RenderWindow& insertWindow, const Font& insertFont);

	// Create buttons in vertical layout
	vector<Button> createVerticalButtons(const vector<string>& buttonTexts,
		float yPosition, float spacing = 15.f,
		Vector2f size = Vector2f(600.f, 50.f),
		int textSize = 22);

	// Create buttons in a horizontal layout
	vector<Button> createHorizontalButtons(const vector<string>& buttonTexts, float yPosition,
		float spacing = 30.f, Vector2f size = Vector2f(200.f, 60.f), int textSize = 24);

	// Create a button centered at specified y position
	void centerButton(Button& button, float yPosition);

private:
	RenderWindow& window;
	const Font& font;
};

