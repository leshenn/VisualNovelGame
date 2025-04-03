#include "ButtonLayout.h"
#include "Button.h"


ButtonLayout::ButtonLayout(RenderWindow& window, Font& font) : window(window), font(font) {}


// Create and load play button for the menu page
void ButtonLayout::loadPlayButton()
{
	Button playButton = Button("Play", Vector2f(250.f, 80.f), 36, Color(255, 215, 0), Color::Black);
	playButton.setFont(font);
	playButton.setOutline(Color::White, 3.f);
	playButton.setPosition({(window.getSize().x - playButton.getSize().x) / 2.f, window.getSize().y * 0.7f});
	
	playButton.drawTo(window);
}

// Create and load buttons for user to choose
void ButtonLayout::loadWorldButtons()
{
	// Underworld
	Button underWorldButton = Button("Underworld", Vector2f(200.f, 60.f), 24, Color(128, 0, 128), Color::White);
	underWorldButton.setFont(font);

	// Seaworld
	Button seaWorldButton = Button("Sea World", Vector2f(200.f, 60.f), 24, Color(0, 105, 148), Color::White);
	seaWorldButton.setFont(font);

	// Country side
	Button countrySideButton = Button("Country Side", Vector2f(200.f, 60.f), 24, Color(34, 139, 34), Color::White);
	countrySideButton.setFont(font);

	// Set position of buttons
	float buttonSpacing = 30.f;
	float width = underWorldButton.getSize().x + seaWorldButton.getSize().x + countrySideButton.getSize().x + 2 * buttonSpacing;
	float xPosition = (window.getSize().x - width) / 2.f;

	underWorldButton.setPosition({ xPosition, window.getSize().y - 120.f });
	seaWorldButton.setPosition({ xPosition + underWorldButton.getSize().x + buttonSpacing, window.getSize().y - 120.f });
	countrySideButton.setPosition({ xPosition + underWorldButton.getSize().x + seaWorldButton.getSize().x + 2 * buttonSpacing, window.getSize().y - 120.f});


	underWorldButton.drawTo(window);
	seaWorldButton.drawTo(window);
	countrySideButton.drawTo(window);
}
