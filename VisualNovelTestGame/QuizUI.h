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
	void handleEvent(Event& event);


private:

	RenderWindow& window;
	vector<Button> answerButtons;
	GameState& currentState;
	QuizManager manager;
	Question currentQuestion;
	vector<string> options;
	Font font;
	Text questionText;
	Button nextButton;
	//Timer remainingTime;
	//Clock quizTime;
	Text timerLabel;

};

