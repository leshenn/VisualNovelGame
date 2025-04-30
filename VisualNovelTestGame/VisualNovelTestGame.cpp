#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "JsonManager.h"
#include "Button.h"
#include "LoadSprites.h"
#include "GameState.h"
#include "ButtonLayout.h"
#include "GameLogic.h"
#include "Audio.h"
#include "QuizUI.h"
#include "DialogManager.h"
#include "ProgressBar.h"
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <random>
#include <list>
#include "WordGame.hpp"
#include "BossFight.h"
#include "RhythmGame.h"
#include "Bubble.h"
#include "BubbleGame.h"
#include "WinePlayer.h"
#include "SwagBall.h"
#include "WineGame.h"
#include "ForgeGame.h"

using json = nlohmann::json;
using namespace sf;
using namespace std;
const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;

//player attributes
int Health = 85;
bool DashPowerUp = false;
float parryTime = 0.75f;
int baseAttack = 13;
float defense = 1.0f; //0 %
bool ShootPowerUp = false;

void handleMinigameExecution(GameState& currentState, RenderWindow& window, Audio& audio, DialogManager& dialog) {
	audio.toggleBackgroundSound();
	window.setVisible(false);
	// --- Typing Game ---
	if (currentState == GameState::TYPING_GAME) {
		WordGame wordGame;
		wordGame.run(); 
		int score = wordGame.getFinalScore();
		Health = (score / 6) - 13 + 85; // Apply score penalty/bonus relative to a baseline
		Health = (Health <= 0) ? 1 : Health; // Ensure health doesn't drop below 1
		string text = (Health > 85) ? "Your focus sharpens! Your health increases to " : "Your mind wanders... health decreases to "; 
		text += to_string(Health);
		dialog.setMingameResult(text);
		currentState = (score>74)?  GameState::ATHENA_WIN_SCENE : GameState::ATHENA_LOSE_SCENE;
	}
	// --- Forge Game ---
	else if (currentState == GameState::FORGE_GAME) {
		ForgeGame forgeGame; 
		forgeGame.run();
		int score = forgeGame.getScore();
		int attackChange = (score - 200) / 60; // Calculate attack change based on score vs threshold
		baseAttack += attackChange;
		baseAttack = (baseAttack < 1) ? 1 : baseAttack; // Ensure attack doesn't drop below 1
		string text = (attackChange >= 0) ? "You forged a sharper weapon! +" : "Your weapon feels dull... -";
		text += to_string(attackChange) + " Attack. Base Attack is now " + to_string(baseAttack);
		dialog.setMingameResult(text);
		currentState = (score>199)? GameState::HEPHAESTUS_WIN_SCENE: GameState::HEPHAESTUS_LOSE_SCENE;
	}
	// --- Rhythm Game ---
	else if (currentState == GameState::RHYTHM_GAME) {
		RhythmGame rhythmGame;
		rhythmGame.run();
		float score = rhythmGame.getScore();
		// Calculate ratio relative to a baseline score (e.g., 50) over a range (e.g., 100)
		float ratio = (score - 50.0f) / 100.0f;
		float parryTimeChange = (0.75f * ratio); // Calculate change based on base parry time
		parryTime += parryTimeChange;
		parryTime = (parryTime < 0.1f) ? 0.1f : parryTime; // Ensure parry time doesn't become too low
		string text = (parryTimeChange >= 0) ? "You've mastered the rhythm! +" : "Your timing is off... ";
		text += to_string(parryTimeChange) + "s Parry Window. Total: " + to_string(parryTime) + "s";
		dialog.setMingameResult(text);
		currentState = (score>49)? GameState::APOLLO_WIN_SCENE: GameState::APOLLO_LOSE_SCENE;
	}
	// --- Wine Game ---
	else if (currentState == GameState::WINE_GAME) {
		WineGame wineGame;
		while (wineGame.running()) {
			wineGame.update();
			wineGame.render();
		}
		if (wineGame.getGameWin()) { 
			string text = "The drink invigorates you! You gained DRUNKEN DASH.";
			dialog.setMingameResult(text);
			DashPowerUp = true;
			currentState = GameState::DIONYSUS_WIN_SCENE;
		}
		else {
			string text = "The wine spills... No power-up granted.";
			dialog.setMingameResult(text);
			currentState = GameState::DIONYSUS_LOSE_SCENE;
		}
	}
	// --- Bubble Game ---
	else if (currentState == GameState::BUBBLE_GAME) {
		BubbleGame bubbleGame;
		while (bubbleGame.isRunning()) {
			bubbleGame.handling();
			bubbleGame.update();
			bubbleGame.render();
		}
		if (bubbleGame.getBubbleGameWon()) {
			string text = "A strange energy flows through you! Gained ARCANE SHOT."; 
			dialog.setMingameResult(text);
			ShootPowerUp = true;
			currentState = GameState::POSEIDON_WIN_SCENE;
		}
		else {
			string text = "The bubbles pop harmlessly... No power-up gained.";
			dialog.setMingameResult(text);
			currentState = GameState::POSEIDON_LOSE_SCENE;
		}
	}
	// --- Boss Game ---
	else if (currentState == GameState::BOSS_GAME) {
		defense = 2.0f - 0.02f * HadesScore*10; //max boss damage 2x and min 0.8x
		defense = (defense < 0.81f) ? 0.8f : defense;
		Player player1(Health, Health, DashPowerUp, parryTime, baseAttack, defense, ShootPowerUp);
		BossGame game(player1);
		game.run();
		currentState = (game.playerWin())? GameState::HADES_TRUE_ENDING:GameState::HADES_FALSE_ENDING; 	
	}
	audio.toggleBackgroundSound();
	window.setVisible(true);
}

int main()
{
	RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Visual Novel");
	window.setFramerateLimit(30);
	LoadSprites loadSprites;
	GameState currentState;
	JsonManager jm;
	Font newFont;
	newFont.loadFromFile("Fonts/norse/Norsebold.otf");
	Audio audio;
	audio.playBackgroundSound();
	DialogManager dialog;
	ProgressBar progressBar(window);
    
	//Store the male and female character
	loadSprites.loadCharacterOptions("Characters/MainCharacter.png", "Characters/Athena.png");

	//This is the play button
	ButtonLayout layout(window, newFont);
	
	currentState = GameState::MENU;
	QuizUI quiz = QuizUI(window, currentState);
	while (window.isOpen()) {
		if (currentState == GameState::BOSS_GAME || currentState == GameState::TYPING_GAME || currentState == GameState::RHYTHM_GAME  || 
			currentState == GameState::WINE_GAME || currentState == GameState::BUBBLE_GAME || currentState == GameState::FORGE_GAME)
		handleMinigameExecution(currentState, window, audio, dialog);

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			quiz.update();
			handleGameLogic(window, currentState, layout, loadSprites, event, audio, quiz, dialog,progressBar, jm);
		}
		//FIX DOUBLE LOADING
		if (quiz.isActive()) {
			quiz.update();
			renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
		}
			
		
		
	}



	return 0;
}

