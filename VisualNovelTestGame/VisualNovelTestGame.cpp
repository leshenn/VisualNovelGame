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

//This is just a test push by Leshen

int main()
{
	RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Visual Novel");
	Texture background;
	Texture MainCharacter;
	Texture Zeus;
	Texture scroll;
	Font font;

	font.loadFromFile("Robot_Font.otf");
	Text dialogText;
	dialogText.setFont(font);
	dialogText.setString("Test Text");
	dialogText.setCharacterSize(24);
	dialogText.setFillColor(Color::Black);
	dialogText.setPosition(400, 375);

	ifstream file("test.json");
	json poesidonData;
	file >> poesidonData;
	vector<json> phraseDialog = poesidonData["poesidon"];

	MainCharacter.loadFromFile("MainCharacter.png");
	Sprite characterSprite(MainCharacter);
	characterSprite.setPosition(0, 220);

	Zeus.loadFromFile("zeus.png");
	Sprite zeusSprite(Zeus);
	zeusSprite.setPosition(620, 220);

	background.loadFromFile("Coliseum.jpg");
	Sprite backgroundSprite(background);
	backgroundSprite.setScale(0.5, 0.5);

	scroll.loadFromFile("scroll.png");
	Sprite scrollSprite(scroll);
	scrollSprite.setScale(0.35, 0.35);
	scrollSprite.setPosition(153, 300);

	//Button
	Button btn1("hello", Vector2f{ 100, 50 }, 20, sf::Color::Green, sf::Color::Black);
	btn1.setPosition({ 200, 200 });


	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}


		window.clear();
		window.draw(backgroundSprite);
		window.draw(scrollSprite);
		window.draw(zeusSprite);
		window.draw(characterSprite);
		window.draw(dialogText);
		
		btn1.drawTo(window);
		
		window.display();
	}
}