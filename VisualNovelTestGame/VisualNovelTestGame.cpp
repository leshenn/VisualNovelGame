#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Button.h"
#include "LoadSprites.h"

using json = nlohmann::json;
using namespace sf;
using namespace std;
const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;

int main()
{
	RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Visual Novel");
	LoadSprites loadSprites;

	loadSprites.loadInstructionScreen("Backgrounds/MenuBackground.png", "Acessories/MenuScroll.png");

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}


		window.clear();
		window.draw(loadSprites.instructionBackgroundSprite);
		window.draw(loadSprites.menuScrollSprite);
		window.display();
	}
}