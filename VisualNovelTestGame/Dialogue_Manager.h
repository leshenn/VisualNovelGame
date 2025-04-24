#pragma once
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <string>

using json = nlohmann::json;
class Dialogue_Manager
{
public:  
	Dialogue_Manager(const std::string& filename);
	//void loadDialogue();
	void setDialogue(const std::string speaker, const std::string type);
	void draw(sf::RenderWindow& window); 

private: 
	sf::Text text;
	sf::Font font; 
	json dialogue;


};

