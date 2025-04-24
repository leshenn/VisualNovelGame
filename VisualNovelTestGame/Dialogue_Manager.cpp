#include "Dialogue_Manager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;



	Dialogue_Manager::Dialogue_Manager(const std::string &filename) {
	
	
	}
	void Dialogue_Manager::setDialogue(const std::string speaker, const std::string type) {
	
	
	}
	void Dialogue_Manager:: draw(sf::RenderWindow& window) {
		window.draw(dialogue);
	}




