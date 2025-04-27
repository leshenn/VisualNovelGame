#pragma once

#include <SFML/Graphics.hpp>
#include "JsonManager.h"
#include "GameState.h"
#include "ButtonLayout.h"
#include "LoadSprites.h"
#include "Audio.h"
#include "QuizUI.h"
#include "DialogManager.h"
#include "ProgressBar.h"

using namespace sf;

static bool playerIsMale; // true for male, false for female

static void setPlayerGender(bool isMale) { playerIsMale = isMale; }

static bool getPlayerGender() { return playerIsMale; }

void loadGameAssets(GameState currentState, LoadSprites& loadSprites, DialogManager& dialog);

void renderGameScene(RenderWindow& window, GameState currentState, ButtonLayout& layout, LoadSprites& loadSprites, QuizUI& quiz, DialogManager& dialog, Audio& audio,ProgressBar& progressBar);

void handleGameLogic(RenderWindow& window, GameState& currentState, 
	ButtonLayout& layout, LoadSprites& loadSprites, Event& event, Audio& audio, QuizUI& quiz, DialogManager& dialog,ProgressBar& progressBar, JsonManager& jm);

static int totalScore = 0;