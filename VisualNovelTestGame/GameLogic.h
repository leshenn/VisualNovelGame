#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "ButtonLayout.h"
#include "LoadSprites.h"
#include "Audio.h"

using namespace sf;

void loadGameAssets(GameState currentState, LoadSprites& loadSprites);

void renderGameScene(RenderWindow& window, GameState currentState, ButtonLayout& layout, LoadSprites& loadSprites);

void handleGameLogic(RenderWindow& window, GameState& currentState, 
	ButtonLayout& layout, LoadSprites& loadSprites, Event& event, Audio& audio);