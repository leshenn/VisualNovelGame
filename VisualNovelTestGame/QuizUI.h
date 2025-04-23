#pragma once
#include "Button.h"
#include "Question.h"
#include "QuizManager.h"
#include <vector>
#include <SFML/Window.hpp>
#include "Audio.h"

using namespace sf;

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
	void update();
	void resetQuiz();
	int getScore() { return manager.getScore(); }
	
	// Function template to center elements
	template<typename T>
	void centerPosition(T& element, float yPosition) {
		FloatRect bounds = element.getLocalBounds();
		element.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
		element.setPosition(window.getSize().x / 2.f, yPosition);
	}


private:
	//timer functions
	float timeRemaining;
	Clock quizTimer;
	Text timerText;


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

