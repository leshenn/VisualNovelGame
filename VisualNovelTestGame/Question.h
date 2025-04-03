#pragma once
#include <string>
#include <vector>

using namespace std;

// Question class representing a quiz question with multiple choice answers
class Question {
public:
    // Constructors
    Question();
    Question(const string& instertQuestionText, const vector<string>& insertOptions, int instertCorrectAnswerIndex);

    // Getters
    string getQuestionText() const;
    vector<string> getOptions() const;
    bool isCorrect(int answerIndex) const;
    int getCorrectAnswerIndex() const;

private:
    string questionText; // The question being asked
    vector<string> options; // Possible answers
    int correctAnswerIndex; // Index of correct answer in options vector
};