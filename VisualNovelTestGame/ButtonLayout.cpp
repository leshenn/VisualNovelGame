#include "ButtonLayout.h"

using namespace std;
using namespace sf;

ButtonLayout::ButtonLayout(RenderWindow& window, const Font& font) : window(window), font(font) {}

vector<Button> ButtonLayout::createVerticalButtons(const vector<string>& buttonTexts,
	float yPosition, float spacing, Vector2f size, int textSize)
{
	vector<Button> buttons;
	return buttons;
}