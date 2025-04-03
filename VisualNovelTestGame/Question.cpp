#include "Question.h"

// Default constructor
Question::Question() {}

// Parameterized constructor - creates a complete question
Question::Question(const std::string& questionText,
    const std::vector<std::string>& options,
    int correctAnswerIndex)
    : questionText(questionText), options(options), correctAnswerIndex(correctAnswerIndex) {
}

// Returns the question text
std::string Question::getQuestionText() const { return questionText; }

// Returns all answer options
std::vector<std::string> Question::getOptions() const { return options; }

// Checks if the selected answer is correct
bool Question::isCorrect(int answerIndex) const {
    return answerIndex == correctAnswerIndex;
}

// Returns the index of the correct answer
int Question::getCorrectAnswerIndex() const {
    return correctAnswerIndex;
}