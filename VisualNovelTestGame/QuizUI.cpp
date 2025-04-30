#include "QuizUI.h"
#include "GameState.h"
#include "Question.h"
#include "Button.h"
#include "Audio.h"
#include "GameLogic.h"


using namespace std;
using namespace sf;


QuizUI::QuizUI(RenderWindow& window, GameState& state) : window(window), currentState(state), scoreShown(false), showingResult(false) {

	// Load questions
	font.loadFromFile("Fonts/norse/Norsebold.otf");
	manager.loadQuestions(currentState);

	//intialise progress bar
	progressbar.setFillColor(Color::Red);

	progressbarOutline.setFillColor(Color::Transparent);
	progressbarOutline.setOutlineColor(Color::Black);

	// Score display configuration
	scoreText.setFont(font);
	scoreText.setCharacterSize(45);
	scoreText.setFillColor(sf::Color::White);

	//Quiz timer text configuration
	timerText.setFont(font);
	timerText.setCharacterSize(28);
	timerText.setFillColor(sf::Color::Black);

	// Result text configuration (correct/wrong feedback)
	resultText.setFont(font);
	resultText.setCharacterSize(32);
	resultText.setFillColor(sf::Color::Green);

	// Initialise question text
	questionText.setFont(font);
	questionText.setCharacterSize(23);
	questionText.setFillColor(Color::Black);

	// Initialise Next Button
	nextButton = Button("Next", Vector2f(150.f, 50.f), 24, Color(200, 200, 200), Color::Black);
	nextButton.setFont(font);
	nextButton.setOutline(Color::White, 2.f);


	showingResult = false;
}

void QuizUI::initQuiz(GameState world) {
	// ONLY CALL THIS WHEN STARTING A NEW QUIZ
	Active = true;
	currentState = world; // Update the current state
	manager.loadQuestions(currentState);
	refreshQuizUI();
}

void QuizUI::refreshQuizUI()
{	
	answerButtons.clear();
	currentQuestion = manager.getCurrentQuestion();
	options = currentQuestion.getOptions();

	// Create answer buttons
	for (size_t i = 0; i < options.size(); ++i)
	{
		Button answerButton(options[i], Vector2f(500.f, 45.f), 22, Color(70, 70, 70), Color::White);
		answerButton.setFont(font);

		// Push Button into the answerButtons vector
		answerButtons.push_back(answerButton);
	}

	//initialize timer
	manager.questionTimer.reset();
	manager.questionTimer.start();
	quizTimer.restart();
	progressbarOutline.setSize(Vector2f(50 * manager.questionTimer.getTimeRemaining(), 30));
	progressbarOutline.setOutlineThickness(2);


	//Timer related position code
	timerText.setString("Time: " + std::to_string((int)timeRemaining) + "s");
	FloatRect timerBounds = timerText.getLocalBounds();
	progressbar.setOrigin(timerBounds.width / 2.0f, timerBounds.height / 2.0f);
	progressbar.setPosition((window.getSize().x / 2.f)- (50 * manager.questionTimer.getTimeRemaining() / 2.f) +50.f, 675.f);

	progressbarOutline.setOrigin(timerBounds.width / 2.0f, timerBounds.height / 2.0f);
	progressbarOutline.setPosition((window.getSize().x / 2.f)- (50 * manager.questionTimer.getTimeRemaining() / 2.f)+50.f, 675.f);

	centerPosition(timerText, 65.f);

	


	// Position answer buttons
	float yPosition = window.getSize().y * 0.4f;
	float spacing = 15.f;
	const float columnSpacing = 10.f; // Adjust spacing between columns
	const float rowSpacing = 10.f; // Adjust spacing between rows
	const int columns = 2; // Two buttons per row

	for (size_t i = 0; i < answerButtons.size(); ++i) {
		int row = i / columns;
		int col = i % columns;

		float xPos = (window.getSize().x / 2.f) + (col * (answerButtons[i].getSize().x + columnSpacing)) -
			((columns - 1) * (answerButtons[i].getSize().x + columnSpacing) / 2.f) - 250;

		float yPos = yPosition + row * (answerButtons[i].getSize().y + rowSpacing) + 230;

		answerButtons[i].setPosition({xPos ,yPos});
	}

	// Set the question text for the current question
	questionText.setString(currentQuestion.getQuestionText());
	centerPosition(questionText, window.getSize().y * 0.68f);

	updateScoreText(); // Refresh score display
	scoreText.setPosition(1000.f, 20.f); // Top-left position

	// Position next button in bottom-right corner
	nextButton.setPosition({
		window.getSize().x - nextButton.getSize().x - 20.f,
		window.getSize().y - nextButton.getSize().y - 20.f
		});

	showingResult = false; // Reset result display state


}

void QuizUI::updateScoreText()
{
	scoreText.setString("Score: " + to_string(manager.getScore()) +
		" out of " + to_string(manager.getTotalQuestions()));
}

// Show result feedback (correct/wrong)
void QuizUI::showResult(bool isCorrect) {
	
	showingResult = true;

	if (isCorrect) {
		audio.playCorrectAnswerSound();
		resultText.setString("Correct!");
		resultText.setFillColor(sf::Color::Green);
	}
	else {
		audio.playIncorrectAnswerSound();
		resultText.setString("Wrong!");
		resultText.setFillColor(sf::Color::Red);
	}

	// Center the result text above the question
	centerPosition(resultText, window.getSize().y * 0.2f);
}

// Handle Quiz event
void QuizUI::handleEvent()
{
	if (!showingResult && !manager.isQuizComplete()) {
		// Check which answer button was clicked
		for (size_t i = 0; i < answerButtons.size(); ++i) {
			if (answerButtons[i].isMouseOver(window)) {
				bool isCorrect = manager.answerCurrentQuestion(i);
				
				if (isCorrect)
				{
					answerButtons[i].setBackColor(Color::Green);
				}
				else if (!isCorrect) {
					answerButtons[i].setBackColor(Color::Red);
				}

				showResult(isCorrect); // Show feedback
				updateScoreText(); // Update score display
				break;
			}
		}
	}
	else if (nextButton.isMouseOver(window)) {
		loadNextQuestion(); // Proceed to next question
		audio.playClickButtonSound();
	}
}

// Load the next question or show final score if quiz complete
void QuizUI::loadNextQuestion() {
	refreshQuizUI();
	manager.nextQuestion();
	showingResult = false;

	if (manager.isQuizComplete()) {
		showFinalScore();
		timerText.setString("");
	}
	else {
		refreshQuizUI(); // Set up UI for next question
	}
}

// Show final score screen
void QuizUI::showFinalScore() {

	//hide progress bar
	progressbarOutline.setOutlineThickness(0);
	progressbar.setSize(Vector2f(0 , 0));

	questionText.setString("Quiz Complete!");
	questionText.setCharacterSize(50);
	centerPosition(questionText, window.getSize().y * 0.77f);

	// Create final score display text
	std::string resultStr = "Final Score: " + std::to_string(manager.getScore()) +
		" out of " + std::to_string(manager.getTotalQuestions());
	answerButtons.clear();

	// Create a special button to display the final score
	Button finalScoreButton(resultStr, sf::Vector2f(400.f, 80.f), 32, sf::Color::Transparent, sf::Color::White);
	finalScoreButton.setFont(font);
	finalScoreButton.setPosition({
		(window.getSize().x - finalScoreButton.getSize().x) / 2.f, // Center horizontally
		window.getSize().y * 0.5f // Middle of screen vertically
		});
	answerButtons.push_back(finalScoreButton);
	scoreShown = true;
	Active = false;
}

// Draw to window
void QuizUI::render()
{
	window.draw(progressbarOutline);
	window.draw(progressbar);
	window.draw(timerText);
	
	window.draw(questionText);
	window.draw(scoreText);

	// Draw answer buttons
	for (auto& button : answerButtons) {
		button.drawTo(window);
	}

	// Show result and next button when appropriate
	if (showingResult) {
		window.draw(resultText);
		nextButton.drawTo(window);
	}
	else if (manager.isQuizComplete()) {
		nextButton.drawTo(window); // Show next button on final screen
	}
}

void QuizUI::update() {
	if (!manager.isQuizComplete()) {
		if (!showingResult) {
			manager.update(quizTimer.restart().asSeconds());

			if (manager.questionTimer.isFinished()) {
				showResult(false); // Auto-fail when time runs out
				updateScoreText();
			}

			// Update timer display
			timerText.setString(manager.questionTimer.getTimeString());
			progressbar.setSize(Vector2f(50 * manager.questionTimer.getTimeRemaining(), 30));
		}
	}
}

void QuizUI::resetQuiz() {
	// Reset all state variables
	scoreShown = false;
	showingResult = false;

	// Fully reset the manager
	manager.reset();
	manager.setComplete(false); // Explicitly mark as not complete

	// Reset UI elements
	timeRemaining = 10.0f;
	quizTimer.restart();
	answerButtons.clear();
	questionText.setCharacterSize(23);

	// Reload questions
	manager.loadQuestions(currentState);
}

bool QuizUI::isActive() {
	return Active;
}