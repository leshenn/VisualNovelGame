#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"
#include "GameState.h"
#include "QuizUI.h"

using namespace std;
using namespace sf;

class ButtonLayout
{
public:
	ButtonLayout(RenderWindow& window, Font& font);
	void loadPlayButton();
	bool playButtonClicked(RenderWindow& window);
	Button& getPlayButton();
	void loadNextButton();
	bool nextButtonClicked(RenderWindow& window);
	Button& getNextButton();
	void loadStageOneButtons();
	Button& getUnderworldButton();
	Button& getSeaWorldButton();
	Button& getCountrySideButton();
	void loadStageTwoButtons();
	Button& getAthensButton();
	Button& getDelphiButton();
	GameState loadStageOneButtonClicked(const sf::Vector2i& mousePos);
	GameState loadStageTwoButtonClicked(const sf::Vector2i& mousePos);
	void loadQuizButtons(GameState& currentState);

private:
	RenderWindow& window;
	Font font;

	Button playButton;  // Store Play button
	Button nextButton;  // Store Next button
	vector<Button> answerButtons; // Store Answer buttons
	Button underWorldButton, seaWorldButton, countrySideButton; // Store stage one buttons
	Button athensButton, delphiButton;		// Store stage two buttons
};

