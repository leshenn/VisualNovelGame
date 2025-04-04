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
	
	// Initialise timer label
	timerLabel.setFont(font);
	timerLabel.setCharacterSize(15);
	timerLabel.setPosition(window.getSize().x / 2.f, 50.f);

	// Initialise question text
	questionText.setFont(font);
	questionText.setCharacterSize(28);
	questionText.setFillColor(Color::Black);

	// Initialise Next Button
	nextButton = Button("Next", Vector2f(150.f, 50.f), 24, Color(200, 200, 200), Color::Black);
	nextButton.setFont(font);
	nextButton.setOutline(Color::White, 2.f);
	nextButton.setPosition({ window.getSize().x - nextButton.getSize().x - 20.f,
							 window.getSize().y - nextButton.getSize().y - 20.f });

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

	// Draw answer buttons
		for (auto& button : answerButtons) {
			button.drawTo(window);
		}

	if (manager.isQuizComplete()) {
		nextButton.drawTo(window); // Show next button on final screen
	}


}

void QuizUI::handleEvent(Event& event)
{
	loadQuiz();
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		if (!manager.isQuizComplete())
		{
			// Check which answer button was clicked
			for (size_t i = 0; i < answerButtons.size(); ++i) {
				if (answerButtons[i].isMouseOver(window)) {
					bool isCorrect = manager.answerCurrentQuestion(i);
					//showResult(isCorrect); // Show feedback
					//updateScoreText(); // Update score display
					break;
				}
			}
		}
		else if (nextButton.isMouseOver(window))
		{
			loadNextQuestion();
		}

	}
		
}

void QuizUI::loadNextQuestion()
{
	manager.nextQuestion();
	if (manager.isQuizComplete())
	{

	}
	else
	{
		loadQuiz();
	}
}