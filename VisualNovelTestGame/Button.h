#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
class Button
{
public:
	Button();
	Button(string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor);
	void setFont(sf::Font& font);
	void setBackColor(sf::Color color);
	void setTextColor(sf::Color color);
	void setPosition(sf::Vector2f pos);
	void drawTo(sf::RenderWindow& window);
	bool isMouseOver(sf::RenderWindow& window);
	void setOutline(sf::Color color, float thickness);


	sf::Vector2f getSize() const
	{
		return button.getSize();
	}

	sf::Vector2f getPosition() const
	{
		return button.getPosition();
	}



private:
	sf::RectangleShape button;
	sf::Text text;
};