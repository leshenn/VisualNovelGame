#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Button.h"

using json = nlohmann::json;
using namespace sf;
using namespace std;
const int WIN_WIDTH = 890;
const int WIN_HEIGHT = 448;
Vector2u windowSize;

//This is just a test push by Leshen
// This is test by Yathish
//	This is test by Rahil


enum class GameState {
	MENU,
	POSEIDON_CONVO,
	HADES_CONVO,
	DIONYSUS_CONVO,
	END
};

void loadScene(GameState state, Texture& backgroundTexture, Sprite& backgroundSprite,
	Texture& godTexture, Sprite& godSprite, Texture& scrollTexture, Sprite& scrollSprite,
	Texture& mainCharacterTexture, Sprite& mainCharacterSprite, Font& font, Text& dialogText) {

	string backgroundFile, characterFile, dialog;

	//load main character
	mainCharacterTexture.loadFromFile("Characters/MainCharacter.png");
	mainCharacterSprite.setTexture(mainCharacterTexture);
	mainCharacterSprite.setPosition(5, 220);

	switch (state) {
	case GameState::POSEIDON_CONVO:
		backgroundFile = "Backgrounds/PoseidonBackground.jpg";
		characterFile = "Characters/Poseidon.png";
		dialog = "I am Poseidon, God of the Seas.";
		break;
	case GameState::HADES_CONVO:
		backgroundFile = "Backgrounds/HadesBackground.jpg";
		characterFile = "Characters/Hades.png";
		dialog = "Welcome to the underworld...";
		break;
	case GameState::DIONYSUS_CONVO:
		backgroundFile = "Backgrounds/DionysusBackground.jpg";
		characterFile = "Characters/Dionysus.png";
		dialog = "      Drink and be merry!";
		break;
	case GameState::END:
		backgroundFile = "Backgrounds/Coliseum.jpg";
		characterFile = "Characters/Zeus.png";
		dialog = "Your journey has ended.";
		break;
	default:
		backgroundFile = "";
		characterFile = "";
		dialog = "Welcome to the game.";
		break;
	}

	// Load Background
	backgroundTexture.loadFromFile(backgroundFile);
	Vector2u textureSize = backgroundTexture.getSize();
	// Calculate scale factors to make the image fit the screen
	float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
	float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(scaleX, scaleY);
	backgroundSprite.setPosition(0, 0);

	// Load Character
	if (!characterFile.empty()) {
		godTexture.loadFromFile(characterFile);
		godSprite.setTexture(godTexture);
		godSprite.setPosition(600, 220);
		godSprite.setScale(1, 1);
	}

	// Load Dialog Scroll
	scrollTexture.loadFromFile("scroll.png");
	scrollSprite.setTexture(scrollTexture);
	scrollSprite.setScale(0.36, 0.36);
	scrollSprite.setPosition(155, 300);

	// Set Dialog Text
	font.loadFromFile("Robot_Font.otf");
	dialogText.setFont(font);
	dialogText.setString(dialog);
	dialogText.setCharacterSize(24);
	dialogText.setFillColor(Color::Black);
	dialogText.setPosition(300, 375);

}

int main()
{
	RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Visual Novel");
	Texture backgroundTexture, mainCharacterTexture, godTexture, scrollTexture;
	Sprite backgroundSprite, mainCharacterSprite, godSprite, scrollSprite;
	Font font;
	font.loadFromFile("Robot_Font.otf");
	Text dialogText;
	windowSize = window.getSize();

	// Set game state to start with the poseidon conversation(can be changed to the menu)
	GameState currentState = GameState::POSEIDON_CONVO;

	//Loads the states to allow the poseidon state will be shown
	loadScene(currentState, backgroundTexture, backgroundSprite, 
		godTexture, godSprite, scrollTexture, scrollSprite, 
		mainCharacterTexture, mainCharacterSprite, font, dialogText);

	//This is just to check if the json works, but it is currently not being used
	ifstream file("test.json");
	json poesidonData;
	file >> poesidonData;
	vector<json> phraseDialog = poesidonData["poesidon"];

	// next Button
	Button nextButton("Next", Vector2f{ 50, 25 }, 15, Color::White, Color::Black);
	nextButton.setPosition({ 800, 400 });
	nextButton.setFont(font);



	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			//This check that the button was pressed(over the button)
			if (event.type == Event::MouseButtonPressed && nextButton.isMouseOver(window)) {
				// Transition to the next state(Checks current state then makes the descision)
				if (currentState == GameState::POSEIDON_CONVO)
					currentState = GameState::HADES_CONVO;
				else if (currentState == GameState::HADES_CONVO)
					currentState = GameState::DIONYSUS_CONVO;
				else if (currentState == GameState::DIONYSUS_CONVO)
					currentState = GameState::END;

				//Loads all the scenes in(the first time was just for poseidon)
				loadScene(currentState, backgroundTexture, backgroundSprite,
					godTexture, godSprite, scrollTexture, scrollSprite,
					mainCharacterTexture, mainCharacterSprite, font, dialogText);
			}

		}


		window.clear();
		window.draw(backgroundSprite);
		window.draw(scrollSprite);
		window.draw(godSprite);
		window.draw(mainCharacterSprite);
		window.draw(dialogText);
		nextButton.drawTo(window);
		window.display();
	}
	return 0;
}