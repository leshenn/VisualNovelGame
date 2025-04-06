#include "ButtonLayout.h"
#include "Button.h"
#include "QuizManager.h"
#include "GameState.h"
#include <vector>
#include "QuizUI.h"


ButtonLayout::ButtonLayout(RenderWindow& window, Font& font) : window(window), font(font) {}

// Load quiz buttons
void ButtonLayout::loadQuizButtons(GameState& currentState)
{

	vector<Button> answerButtons;

	QuizManager newQuiz;
	newQuiz.loadQuestions(currentState);

	const Question& currentQuestion = newQuiz.getCurrentQuestion();
	vector<string> options = currentQuestion.getOptions();

	// Create answer button for each option
	for (size_t i = 0; i < options.size(); ++i)
	{
		Button answerButton(options[i], Vector2f(600.f, 50.f), 22, Color(70, 70, 70), Color::White);
		answerButton.setFont(font);

		// Push Button into the answerButtons vector
		answerButtons.push_back(answerButton);
	}

	// Set position for the answer buttons
	float yPosition = window.getSize().y * 0.4f;
	float spacing = 15.f;

	for (size_t i = 0; i < answerButtons.size(); ++i)
	{
		answerButtons[i].setPosition({ (window.getSize().x - answerButtons[i].getSize().x) / 2.f, // Center the buttons
										yPosition + i * (answerButtons[i].getSize().y + spacing) }); // Vertically align buttons
	}

	// Draw to window
	for (auto& button : answerButtons)
	{
		button.drawTo(window);
	}

}


// Create and load play button for the menu page
void ButtonLayout::loadPlayButton()
{
	playButton = Button("Play", Vector2f(250.f, 80.f), 36, Color(255, 215, 0), Color::Black);
	playButton.setFont(font);
	playButton.setOutline(Color::White, 3.f);
	playButton.setPosition({(window.getSize().x - playButton.getSize().x) / 2.f, window.getSize().y * 0.7f});
	
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
	// Underworld
	underWorldButton = Button("Underworld", Vector2f(200.f, 60.f), 24, Color(128, 0, 128), Color::White);
	underWorldButton.setFont(font);

	// Seaworld
	seaWorldButton = Button("Sea World", Vector2f(200.f, 60.f), 24, Color(0, 105, 148), Color::White);
	seaWorldButton.setFont(font);

	// Country side
	countrySideButton = Button("Country Side", Vector2f(200.f, 60.f), 24, Color(34, 139, 34), Color::White);
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


// Create and load buttons for user to choose
void ButtonLayout::loadStageTwoButtons()
{
	// Athens
	athensButton = Button("Athens", Vector2f(200.f, 60.f), 24, Color(128, 0, 128), Color::White);
	athensButton.setFont(font);

	// Delphi
	delphiButton = Button("Delphi", Vector2f(200.f, 60.f), 24, Color(34, 139, 34), Color::White);
	delphiButton.setFont(font);

	// Set position of buttons
	float buttonSpacing = 30.f;
	float width = athensButton.getSize().x + delphiButton.getSize().x + 2 * buttonSpacing;
	float xPosition = (window.getSize().x - width) / 2.f;

	athensButton.setPosition({ xPosition, window.getSize().y - 120.f });
	delphiButton.setPosition({ xPosition + athensButton.getSize().x + buttonSpacing, window.getSize().y - 120.f });


	athensButton.drawTo(window);
	delphiButton.drawTo(window);
}

// Check if a button is clicked based on mouse position
GameState ButtonLayout::loadStageOneButtonClicked(const sf::Vector2i& mousePos)
{
	if (seaWorldButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		return GameState::SEAWORLD;
	}
	else if (underWorldButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		return GameState::UNDERWORLD;
	}

	else if (countrySideButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		return GameState::COUNTRY_SIDE;
	}
	else {
		return GameState::STAGE_ONE_MENU;
	}
		
}

GameState ButtonLayout::loadStageTwoButtonClicked(const sf::Vector2i& mousePos)
{

	if (athensButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		return GameState::ATHENS;
	}
	else if (delphiButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		return GameState::DELPHI;
	}
	else {
		return GameState::STAGE_TWO_MENU;
	}

}


//Allows user to access which button was clicked(underWorld/seaWorld/countrySide)
Button& ButtonLayout::getUnderworldButton() { 
	return underWorldButton;
}

Button& ButtonLayout::getSeaWorldButton() { 
	return seaWorldButton;
}

Button& ButtonLayout::getCountrySideButton() { 
	return countrySideButton;
}

Button& ButtonLayout::getAthensButton() {
	return athensButton;
}

Button& ButtonLayout::getDelphiButton() {
	return delphiButton;
}
