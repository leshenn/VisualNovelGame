#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Button.h"
#include "LoadSprites.h"
#include "GameState.h"
#include "ButtonLayout.h";
#include "GameLogic.h"
#include "QuizUI.h"
#include "QuizManager.h"


using json = nlohmann::json;
using namespace sf;
using namespace std;
const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;

int main()
{
	RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Visual Novel");
	LoadSprites loadSprites;
	GameState currentState;
	Font newFont;
	newFont.loadFromFile("Robot_Font.otf");

	//This is the play button
	ButtonLayout layout(window, newFont);

	currentState = GameState::MENU;
	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			handleGameLogic(window, currentState, layout, loadSprites, event);
		}

	}

	return 0;
}