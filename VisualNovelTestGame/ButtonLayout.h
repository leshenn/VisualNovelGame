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
	GameState loadStageOneButtonClicked(const sf::Vector2i& mousePos);

	void loadPoseidonChoiceButtons();
	GameState loadPoseidonChoiceButtonClicked(const sf::Vector2i& mousePos);
	Button& getSeaWorldButton();

	void loadDionysusChoiceButtons();
	GameState loadDionysusChoiceButtonClicked(const sf::Vector2i& mousePos);
	Button& getCountrySideButton();

	void loadStageTwoButtons();
	GameState loadStageTwoButtonClicked(const sf::Vector2i& mousePos);

	Button& getMusicButton();
	Button& getSmokeButton();
	Button& getSignsButton();


private:
	RenderWindow& window;
	Font font;

	Button playButton;  // Store Play button

	Button nextButton;  // Store Next button

	vector<Button> answerButtons; // Store Answer buttons

	Button bluePortal, greenPortal; // Store stage one buttons
	Button atlantisButton, shrineButton; // Store Poseidon choice buttons
	Button pegasusButton, strangerButton; // Store Dionysus choice buttons

	Button musicButton, smokeButton, signsButton;		// Store stage two buttons
};