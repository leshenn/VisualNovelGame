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

int main()
{
	int Health = 85;
	bool DashPowerUp = false;
	float parryTime = 0.75f;
	int baseAttack = 13;
	float defense = 1.0f; //0 %
	bool ShootPowerUp = false;
	
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



		
		/*if (currentState == GameState::TYPING_GAME) {
			audio.toggleBackgroundSound();
			WordGame wordGame;
			wordGame.run();                           //-13 need 75 or higher for no penalty
			Health = (wordGame.getFinalScore() / 6) - 13 + 85;
			Health = (Health <= 0) ? 1 : Health;
			if (wordGame.getGameOver()) {
				string text = (Health > 100) ? "This has granted you " : "Failed you are down to ";
				text += Health + " health.";
				dialog.setMingameResult(text);
				currentState = GameState::FORGE_GAME;
				window.setVisible(true);
			}
			audio.toggleBackgroundSound();
		}
		if (currentState == GameState::FORGE_GAME){
			audio.toggleBackgroundSound();
			ForgeGame Forgegame;
			Forgegame.run();
			baseAttack = ((Forgegame.getScore() - 200) / 60) + 13;
			string text = (baseAttack > 13) ? "You made a sharper knife + " : "You've dulled your knife -";
            text += to_string((Forgegame.getScore() - 200) / 60) + " attack";
			dialog.setMingameResult(text);
			window.setVisible(true);
			currentState = GameState::RHYTHM_GAME;
			audio.toggleBackgroundSound();
        }
		if (currentState == GameState::RHYTHM_GAME) {
			audio.toggleBackgroundSound();
			RhythmGame rhythmGame;
			rhythmGame.run();
			float score = rhythmGame.getScore();
			float ratio = (score - 50) / 100;
			parryTime += (0.75f * ratio);
			string text = (parryTime > 0.75f) ? "You have mastered timing + " : "Bad rhythm -";
			text += to_string(0.75f * ratio) + " parry time";
			dialog.setMingameResult(text);
			currentState = GameState::WINE_GAME;
			window.setVisible(true);
			audio.toggleBackgroundSound();
		}
		if (currentState == GameState::WINE_GAME) {
			audio.toggleBackgroundSound();
			WineGame Winegame;
			while (Winegame.running()){
				Winegame.update();
				Winegame.render();
			}
			if (Winegame.getGameWin()) {
				string text = "You have gained DRUNKEN DASH";
				dialog.setMingameResult(text);
				DashPowerUp = true;
			}
			currentState = GameState::BUBBLE_GAME;
			window.setVisible(true);
			audio.toggleBackgroundSound();
		}
		if (currentState == GameState::BUBBLE_GAME) {
			audio.toggleBackgroundSound();
			BubbleGame bubble;
			while (bubble.isRunning()) {
				bubble.handling();
				bubble.update();
				bubble.render();
			}
			if(bubble.getBubbleGameWon()){
				string text = "You have gained shoot shoot";
				dialog.setMingameResult(text);
				ShootPowerUp = true;
			}
			currentState = GameState::BOSS_GAME;
			window.setVisible(true);
			audio.toggleBackgroundSound();
		}
		if (currentState == GameState::BOSS_GAME) {
			audio.toggleBackgroundSound();
			Player player1(Health, Health, DashPowerUp, parryTime, baseAttack, 1.0f, ShootPowerUp);
			BossGame game(player1);
			game.run();
			currentState = GameState::NYX1;
			window.setVisible(true);
			audio.toggleBackgroundSound();
		}*/

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			quiz.update();
			handleGameLogic(window, currentState, layout, loadSprites, event, audio, quiz, dialog,progressBar, jm);
		}

		//FIX DOUBLE LOADING
	
			//quiz.update();
			//renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio,progressBar);
		
		
	}



	return 0;
}

