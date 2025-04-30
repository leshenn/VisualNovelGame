#include "ButtonLayout.h"
#include "Button.h"
#include "QuizManager.h"
#include "GameState.h"
#include <vector>
#include "QuizUI.h"


ButtonLayout::ButtonLayout(RenderWindow& window, Font& font) : window(window), font(font) {}


// Create and load play button for the menu page
void ButtonLayout::loadPlayButton()
{
	playButton = Button("Play", Vector2f(250.f, 80.f), 36, Color(255, 215, 0), Color::Black);
	playButton.setFont(font);
	playButton.setOutline(Color::White, 3.f);
	playButton.setPosition({ (window.getSize().x - playButton.getSize().x) / 2.f, window.getSize().y * 0.7f });

	playButton.drawTo(window);
}


// Check if the play button is clicked
bool ButtonLayout::playButtonClicked(RenderWindow& window) {
	Vector2i mousePos = Mouse::getPosition(window);
	return playButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos));
}

// Allows user to get the button
Button& ButtonLayout::getPlayButton() {
	return playButton;
}

void ButtonLayout::loadNextButton()
{
	// Create next button
	nextButton = Button("Next", Vector2f(150.f, 50.f), 24, Color(200, 200, 200), Color::Black);
	nextButton.setFont(font);
	nextButton.setOutline(Color::White, 2.f);

	// Set position of Next button
	nextButton.setPosition({ window.getSize().x - nextButton.getSize().x - 20.f,
							 window.getSize().y - nextButton.getSize().y - 20.f });

	nextButton.drawTo(window);

}

//	Checks if the next button is clicked
bool ButtonLayout::nextButtonClicked(RenderWindow& window) {
	Vector2i mousePos = Mouse::getPosition(window);
	return nextButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos));
}

// Allows user to access next button
Button& ButtonLayout::getNextButton() {
	return nextButton;
}

// Create and load buttons for user to choose
void ButtonLayout::loadStageOneButtons()
{
	// Country side
	greenPortal = Button("Green Portal", Vector2f(200.f, 60.f), 24, Color(34, 139, 34), Color::White);
	greenPortal.setFont(font);

	// Seaworld
	bluePortal = Button("Blue Portal", Vector2f(200.f, 60.f), 24, Color(30, 144, 255), Color::White);
	bluePortal.setFont(font);

	// Set position of buttons
	float buttonSpacing = 30.f;
	float width = greenPortal.getSize().x + greenPortal.getSize().x + 2 * buttonSpacing;
	float xPosition = (window.getSize().x - width) / 2.f;

	bluePortal.setPosition({ xPosition, window.getSize().y - 120.f });
	greenPortal.setPosition({ xPosition + greenPortal.getSize().x + buttonSpacing, window.getSize().y - 120.f });


	greenPortal.drawTo(window);
	bluePortal.drawTo(window);
}

// Check if a button is clicked based on mouse position
GameState ButtonLayout::loadStageOneButtonClicked(const sf::Vector2i& mousePos)
{
	if (bluePortal.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		return GameState::POSEIDON_OPENING_SCENE;	
	}
	else if (greenPortal.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		return GameState::DIONYSUS_OPENING_SCENE;	//GameState::DIONYSUS_OPENING_SCENE
	}
	else {
		return GameState::STAGE_ONE_MENU;
	}
	

}


// Create and load buttons for user to choose
void ButtonLayout::loadPoseidonChoiceButtons()
{
	// Atlantis
	atlantisButton = Button("Jump In", Vector2f(200.f, 60.f), 24, Color(128, 0, 128), Color::White);
	atlantisButton.setFont(font);

	// shrine
	shrineButton = Button("Go to the Shrine", Vector2f(200.f, 60.f), 24, Color(0, 105, 148), Color::White);
	shrineButton.setFont(font);

	// Set position of buttons
	float buttonSpacing = 30.f;
	float width = atlantisButton.getSize().x + shrineButton.getSize().x + 2 * buttonSpacing;
	float xPosition = (window.getSize().x - width) / 2.f;

	atlantisButton.setPosition({ xPosition, window.getSize().y - 120.f });
	shrineButton.setPosition({ xPosition + atlantisButton.getSize().x + buttonSpacing, window.getSize().y - 120.f });


	atlantisButton.drawTo(window);
	shrineButton.drawTo(window);
}

// Check if a button is clicked based on mouse position
GameState ButtonLayout::loadPoseidonChoiceButtonClicked(const sf::Vector2i& mousePos)
{
	if (atlantisButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		return GameState::ATLANTIS_SCENE;	//GameState::ATLANTIS_SCENE
	}
	else if (shrineButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		return GameState::SHRINE_SCENE;	//GameState::SHRINE_SCENE
	}
	else {
		return GameState::POSEIDON_CHOICE;
	}

}


// Create and load buttons for user to choose
void ButtonLayout::loadDionysusChoiceButtons()
{
	// pegasus
	pegasusButton = Button("Run after pegasus", Vector2f(200.f, 60.f), 24, Color(128, 0, 128), Color::White);
	pegasusButton.setFont(font);

	// stranger
	strangerButton = Button("Talk to stranger", Vector2f(200.f, 60.f), 24, Color(0, 105, 148), Color::White);
	strangerButton.setFont(font);

	// Set position of buttons
	float buttonSpacing = 30.f;
	float width = pegasusButton.getSize().x + strangerButton.getSize().x + 2 * buttonSpacing;
	float xPosition = (window.getSize().x - width) / 2.f;

	pegasusButton.setPosition({ xPosition, window.getSize().y - 120.f });
	strangerButton.setPosition({ xPosition + pegasusButton.getSize().x + buttonSpacing, window.getSize().y - 120.f });


	pegasusButton.drawTo(window);
	strangerButton.drawTo(window);
}

// Check if a button is clicked based on mouse position
GameState ButtonLayout::loadDionysusChoiceButtonClicked(const sf::Vector2i& mousePos)
{
	std::cout << "TEST LAOD STAGEONE" << endl;
	if (pegasusButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		return GameState::FOREST_SCENE;	//GameState::PEGASUS_SCENE
	}
	else if (strangerButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		return GameState::KOMOS_SCENE;	//GameState::STRANGER_SCENE
	}
	else {
		return GameState::DIONYSUS_CHOICE;
	}

}


// Create and load buttons for user to choose
void ButtonLayout::loadStageTwoButtons()
{
	// Follow music
	musicButton = Button("Follow music", Vector2f(200.f, 60.f), 24, Color(128, 0, 128), Color::White);
	musicButton.setFont(font);

	// Follow smoke trail
	smokeButton = Button("Follow smoke", Vector2f(200.f, 60.f), 24, Color(34, 139, 34), Color::White);
	smokeButton.setFont(font);

	// Follow signs
	signsButton = Button("Follow signs", Vector2f(200.f, 60.f), 24, Color(34, 0, 134), Color::White);
	signsButton.setFont(font);

	// Set position of buttons
	float buttonSpacing = 30.f;
	float width = musicButton.getSize().x + smokeButton.getSize().x + signsButton.getSize().x + 2 * buttonSpacing;
	float xPosition = (window.getSize().x - width) / 2.f;

	musicButton.setPosition({ xPosition, window.getSize().y - 120.f });
	smokeButton.setPosition({ xPosition + musicButton.getSize().x + buttonSpacing, window.getSize().y - 120.f });
	signsButton.setPosition({ smokeButton.getPosition().x + smokeButton.getSize().x + buttonSpacing, window.getSize().y - 120.f });


	musicButton.drawTo(window);
	smokeButton.drawTo(window);
	signsButton.drawTo(window);
}



GameState ButtonLayout::loadStageTwoButtonClicked(const sf::Vector2i& mousePos)
{

	if (musicButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		return GameState::APOLLO_OPENING_SCENE;  //HEPHAESTUS_OPENING_SCENE
	}
	else if (smokeButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		return GameState::HEPHAESTUS_OPENING_SCENE;	//APOLLO_OPENING_SCENE
	}
	else if (signsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		return GameState::ATHENA_OPENING_SCENE;	//ATHENA_OPENING_SCENE
	}
	else {
		return GameState::STAGE_TWO_MENU;
	}

}


//Allows user to access which button was clicked(underWorld/seaWorld/countrySide)

Button& ButtonLayout::getSeaWorldButton() {
	return bluePortal;
}

Button& ButtonLayout::getCountrySideButton() {
	return greenPortal;
}

Button& ButtonLayout::getMusicButton() {
	return musicButton;
}

Button& ButtonLayout::getSmokeButton() {
	return smokeButton;
}

Button& ButtonLayout::getSignsButton() {
	return signsButton;
}