#include "QuizUI.h"
#include "GameState.h"
#include "Question.h"
#include "Button.h"


using namespace std;
using namespace sf;


QuizUI::QuizUI(RenderWindow& window, GameState& state) : window(window), currentState(state) {

	// Load questions
	font.loadFromFile("Robot_Font.otf");
	manager.loadQuestions(currentState);

	// Score display configuration
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);

	// Result text configuration (correct/wrong feedback)
	resultText.setFont(font);
	resultText.setCharacterSize(32);
	resultText.setFillColor(sf::Color::Green);

	// Initialise question text
	questionText.setFont(font);
	questionText.setCharacterSize(28);
	questionText.setFillColor(Color::Black);

	// Initialise Next Button
	nextButton = Button("Next", Vector2f(150.f, 50.f), 24, Color(200, 200, 200), Color::Black);
	nextButton.setFont(font);
	nextButton.setOutline(Color::White, 2.f);

	showingResult = false;
}

void QuizUI::loadQuiz()
{	
	answerButtons.clear();
	currentQuestion = manager.getCurrentQuestion();
	options = currentQuestion.getOptions();

	// Create answer buttons
	for (size_t i = 0; i < options.size(); ++i)
	{
		Button answerButton(options[i], Vector2f(600.f, 50.f), 22, Color(70, 70, 70), Color::White);
		answerButton.setFont(font);

		// Push Button into the answerButtons vector
		answerButtons.push_back(answerButton);
	}

	// Position answer buttons
	float yPosition = window.getSize().y * 0.4f;
	float spacing = 15.f;

	for (size_t i = 0; i < answerButtons.size(); ++i)
	{
		answerButtons[i].setPosition({ (window.getSize().x - answerButtons[i].getSize().x) / 2.f, // Center the buttons
										yPosition + i * (answerButtons[i].getSize().y + spacing) }); // Vertically align buttons
	}

	questionText.setString(currentQuestion.getQuestionText());
	FloatRect questionBounds = questionText.getLocalBounds();
	// Center text origin
	questionText.setOrigin(questionBounds.left + questionBounds.width / 2.0f,
		questionBounds.top + questionBounds.height / 2.0f);
	questionText.setPosition(window.getSize().x / 2.f, window.getSize().y * 0.3f);

	updateScoreText(); // Refresh score display
	scoreText.setPosition(20.f, 20.f); // Top-left position

	// Position next button in bottom-right corner
	nextButton.setPosition({
		window.getSize().x - nextButton.getSize().x - 20.f,
		window.getSize().y - nextButton.getSize().y - 20.f
		});

	showingResult = false; // Reset result display state


}

void QuizUI::updateScoreText()
{
	scoreText.setString("Score: " + std::to_string(manager.getScore()) +
		" out of " + std::to_string(manager.getTotalQuestions()));
}

// Show result feedback (correct/wrong)
void QuizUI::showResult(bool isCorrect) {
	
	showingResult = true;

	if (isCorrect) {
		resultText.setString("Correct!");
		resultText.setFillColor(sf::Color::Green);
	}
	else {
		resultText.setString("Wrong!");
		resultText.setFillColor(sf::Color::Red);
	}

	// Center the result text above the question
	sf::FloatRect resultBounds = resultText.getLocalBounds();
	resultText.setOrigin(resultBounds.left + resultBounds.width / 2.0f,
		resultBounds.top + resultBounds.height / 2.0f);
	resultText.setPosition(window.getSize().x / 2.f, window.getSize().y * 0.2f);
}

// Handle Quiz event
void QuizUI::handleEvent()
{
		
	if (!showingResult && !manager.isQuizComplete()) {
		// Check which answer button was clicked
		for (size_t i = 0; i < answerButtons.size(); ++i) {
			if (answerButtons[i].isMouseOver(window)) {
				bool isCorrect = manager.answerCurrentQuestion(i);
				showResult(isCorrect); // Show feedback
				updateScoreText(); // Update score display
				break;
			}
		}
	}
	else if (nextButton.isMouseOver(window)) {
		loadNextQuestion(); // Proceed to next question
	}
}

// Load the next question or show final score if quiz complete
void QuizUI::loadNextQuestion() {
	manager.nextQuestion();
	if (manager.isQuizComplete()) {
		showFinalScore();
		//timerText.setString("");
	}
	else {
		loadQuiz(); // Set up UI for next question
	}
}

// Show final score screen
void QuizUI::showFinalScore() {
	questionText.setString("Quiz Complete!");

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
}

// Draw to window
void QuizUI::render()
{

	window.draw(questionText);

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
