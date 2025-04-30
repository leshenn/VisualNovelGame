#include "Question.h"

using namespace std;

// Default constructor
Question::Question() {}

// Constructor
Question::Question(const string& insertQuestionText, const vector<string>& insertOptions, int insertCorrectAnswerIndex)
{
    questionText = insertQuestionText;
    options = insertOptions;
    correctAnswerIndex = insertCorrectAnswerIndex;

}

// Returns the question text
string Question::getQuestionText() const
{
    return questionText;
}

// Returns all answer options
vector<string> Question::getOptions() const
{
    return options;
}

// Checks if the selected answer is correct
bool Question::isCorrect(int answerIndex) const
{
    return answerIndex == correctAnswerIndex;
}

// Returns the index of the correct answer
int Question::getCorrectAnswerIndex() const
{
    return correctAnswerIndex;
}