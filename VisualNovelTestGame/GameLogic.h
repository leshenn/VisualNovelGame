#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "ButtonLayout.h"
#include "LoadSprites.h"

void handleGameLogic(sf::RenderWindow& window, GameState& currentState, 
	ButtonLayout& layout, LoadSprites& loadSprites, sf::Event& event);