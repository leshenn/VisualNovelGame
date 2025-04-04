#pragma once
#include "Timer.h"
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
    const Question& getCurrentQuestion() const; // Get current question
    bool answerCurrentQuestion(int answerIndex); // Answer current question
    void nextQuestion(); // Move to next question
    bool isQuizComplete() const; // Check if quiz is finished

    // Getters
    int getScore() const; // Get current score
    int getTotalQuestions() const; // Get total question count
    int getCurrentQuestionIndex() const; // Get current question index
    //void update(float deltaTimer);

private:
    std::vector<Question> questions; // Current set of questions
    int currentQuestionIndex; // Index of current question
    int score; // Player's score
    std::vector<Question> amphitriteQuestions; // All Amphitrite questions
    //Timer questionTimer;

    // Helper methods
    void loadAmphitriteQuestions(); // Load Amphitrite questions
    void selectRandomQuestions(int count); // Select random subset of questions
};