#pragma once
#include "Timer.h"
#include "Question.h"
#include "GameState.h"
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

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
    void setComplete(bool complete) { quizComplete = complete; }

    // Getters
    int getScore() const; // Get current score
    int getTotalQuestions() const; // Get total question count
    int getCurrentQuestionIndex() const; // Get current question index

    //TIMER
    void update(float deltaTimer);
    void reset();

    //FRIENDS
    friend class QuizUI;

private:
    vector<Question> questions; // Current set of questions
    int currentQuestionIndex; // Index of current question
    int score; // Player's score
    vector<Question> quizQuestions;
    Timer<float> questionTimer;
    bool quizComplete;

    // Helper methods
    void loadQuestions(string jsonName, string title); // Load questions
    void selectRandomQuestions(int count); // Select random subset of questions
};