#pragma once
#include "Button.h"
#include "Question.h"
#include "QuizManager.h"
#include <vector>
#include <SFML/Window.hpp>
#include "Audio.h"



class QuizUI
{
public:

	QuizUI(RenderWindow& window, GameState& state);
	void initQuiz(GameState world);  // Loads questions ONLY on first start
	void refreshQuizUI(); // Updates UI without resetting questions
	void loadNextQuestion();
	void handleEvent();
	void updateScoreText();
	void showResult(bool isCorrect);
	void showFinalScore();
	void render();
	bool isQuizComplete() const { return manager.isQuizComplete(); }
	bool isScoreShown() const { return scoreShown; }
	
	


private:

	RenderWindow& window;
	vector<Button> answerButtons;
	GameState& currentState;
	QuizManager manager;
	Question currentQuestion;
	vector<string> options;
	Font font;
	Text questionText;
	Text scoreText;
	Text resultText;
	Button nextButton;
	bool showingResult;
	Audio audio;		// Create audio file
	bool scoreShown = false;

};

