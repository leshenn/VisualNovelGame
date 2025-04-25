#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Button.h"
#include "LoadSprites.h"
#include "GameState.h"
#include "ButtonLayout.h"
#include "GameLogic.h"
#include "Audio.h"
#include "QuizUI.h"
#include "DialogManager.h"
#include "ProgressBar.h"
#include "WordGame.hpp"
#include "BossFight.h"
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <random>
#include <list>
#include "RhythmGame.h"
#include "Bubble.h"
#include "BubbleGame.h"


using json = nlohmann::json;
using namespace sf;
using namespace std;
const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;

int main()
{

	//Rhythm game construction
	RhythmGame rhythmGame;
	rhythmGame.run();
	cout << rhythmGame.getScore() << endl;
	//(50-150) score
	//1.5s max added parry time
	float score = rhythmGame.getScore();
	float ratio = (score - 50) / 100;
	float parryTime = (0.75f * ratio);
	if (parryTime < 0) {
		parryTime = 0;
	}
	cout <<"parry time "<< parryTime << endl;

	//WordGame wordGame;
	//wordGame.run();
	//cout<<"Word game score "<<wordGame.getFinalScore();
	////150-275 divide points by 6 this will be health can get netagive score
	//int health = wordGame.getFinalScore() / 6 + 100;
	//if (health <= 0) {
	//	health = 1;
	//}

	//Boss game construction
	/*Player player1(100, 100, true, 0.75f, 20, 0.0f, true);
	player = player1;*/
	Player player(100, 100, true, 0.75f+parryTime, 13, 0.0f, true);
	BossGame game(player);
	game.run();

	//Bubble game construction
	/*BubbleGame bubble;
	while (bubble.isRunning()) {
		bubble.handling();
		bubble.update();
		bubble.render();
	}*/

	    //Word game construction
		//WordGame Wordgame;
		//Wordgame.run();
    
		/* if (Wordgame.getGameOver()) {
			cout << "Game Over!" << endl;
			cout << "final score is " << Wordgame.getFinalScore() << endl;
		}*/

	RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Visual Novel");
	window.setFramerateLimit(30);
	LoadSprites loadSprites;
	GameState currentState;
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

      /*  if (currentState == GameState::BOSS_GAME) {   
			
			if (game.playerWin()) {
				currentState = GameState::NYX1;
			}
			else {
				currentState = GameState::NYX2;
			}
        }*/

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			quiz.update();
			handleGameLogic(window, currentState, layout, loadSprites, event, audio, quiz, dialog,progressBar);
		}
		quiz.update();
		renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio,progressBar);
	}

	return 0;
}