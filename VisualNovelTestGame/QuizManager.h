#pragma once
#include "Question.h"
#include "GameState.h"
#include <vector>
#include <random>
#include <algorithm>

// Manages the quiz questions and game progression
class QuizManager {
public:
    QuizManager(); // Constructor

    // Quiz control methods
    void loadQuestions(GameState world); // Load questions for specific world
    const Question& getCurrentQuestion() const;
    bool answerCurrentQuestion(int answerIndex);
    void nextQuestion(); 
    bool isQuizComplete() const;

    // Getters
    int getScore() const; 
    int getTotalQuestions() const; 
    int getCurrentQuestionIndex() const;

private:

    std::vector<Question> questions; // Current set of questions
    int currentQuestionIndex; // Index of current question
    int score; // Player's score
    std::vector<Question> amphitriteQuestions; // All Amphitrite questions

    // Helper methods
    void loadAmphitriteQuestions(); // Load Amphitrite questions
    void selectRandomQuestions(int count); // Select random subset of questions
};