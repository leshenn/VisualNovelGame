#pragma once
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
    void loadQuestions(GameState world);
    const Question& getCurrentQuestion() const;
    bool answerCurrentQuestion(int answerIndex);
    void nextQuestion(); 
    bool isQuizComplete() const;

    // Getters
    int getScore() const; 
    int getTotalQuestions() const; 
    int getCurrentQuestionIndex() const;

private:

    vector<Question> questions;
    int currentQuestionIndex;
    int score;
    vector<Question> amphitriteQuestions; // All Amphitrite questions

    
    void loadAmphitriteQuestions(); // Load Amphitrite questions
    void selectRandomQuestions(int count); // Select random subset of questions
};