#pragma once
#include "Button.h"
#include "Question.h"
#include "QuizManager.h"
#include <vector>
#include <SFML/Window.hpp>



class QuizUI
{
public:

	QuizUI(RenderWindow& window, GameState& state);
	void loadQuiz();
	void loadNextQuestion();
	void handleEvent();
	void updateScoreText();
	void showResult(bool isCorrect);
	void showFinalScore();
	void render();
	
	


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


};

