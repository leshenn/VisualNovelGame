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
    void setComplete(bool complete) { quizComplete = complete; }

    // Getters
    int getScore() const; // Get current score
    int getTotalQuestions() const; // Get total question count
    int getCurrentQuestionIndex() const; // Get current question index

    //TIMER
    void update(float deltaTimer);
    void reset();

private:
    std::vector<Question> questions; // Current set of questions
    int currentQuestionIndex; // Index of current question
    int score; // Player's score
    std::vector<Question> hadesQuestions; // All hades questions
    std::vector<Question> poseidonQuestions; // All poseidon questions
    std::vector<Question> dionysusQuestions; // All dionysus questions
    std::vector<Question> athenaQuestions; // All ATHENA questions
    std::vector<Question> apolloQuestions; // All apollo questions
    std::vector<Question> nemesisQuestions; // All nemesis questions
    std::vector<Question> aresQuestions;    // All ares questions
    Timer questionTimer;
    bool quizComplete;

    // Helper methods
    void loadHadesQuestions(); // Load Hades questions
    void loadPoseidonQuestions(); // Load Poseidon questions
    void loadDionysusQuestions(); // Load Dionysus questions
    void loadAthenaQuestions();   // Load Athena questions
    void loadApolloQuestions();   // Load Athena questions
    void loadNemesisQuestions(); // Load Nemesis questions
    void loadAresQuestions();    // Load Ares Questions
    void selectRandomQuestions(int count); // Select random subset of questions
};