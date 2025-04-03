#include "ButtonLayout.h"
#include "Button.h"


ButtonLayout::ButtonLayout(RenderWindow& window, Font font) : window(window), font(font) {}

void ButtonLayout::loadPlayButton()
{
	Button playButton = Button("Play", Vector2f(250.f, 80.f), 36, Color(255, 215, 0), Color::Black);
	playButton.setFont(font);
	playButton.setOutline(Color::White, 3.f);
	playButton.setPosition({(window.getSize().x - playButton.getSize().x) / 2.f, window.getSize().y * 0.7f});
	
	playButton.drawTo(window);
}

