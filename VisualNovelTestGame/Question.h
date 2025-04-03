#pragma once
#include <string>
#include <vector>

// Question class representing a quiz question with multiple choice answers
class Question {
public:
    Question(); // Default constructor
    Question(const std::string& questionText,
        const std::vector<std::string>& options,
        int correctAnswerIndex); // Parameterized constructor

    // Getters
    std::string getQuestionText() const; // Returns the question text
    std::vector<std::string> getOptions() const; // Returns all answer options
    bool isCorrect(int answerIndex) const; // Checks if answer is correct
    int getCorrectAnswerIndex() const; // Returns index of correct answer

private:
    std::string questionText; // The question being asked
    std::vector<std::string> options; // Possible answers
    int correctAnswerIndex; // Index of correct answer in options vector
};