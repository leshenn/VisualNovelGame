#include "QuizManager.h"
#include "GameState.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;
using json = nlohmann::json;


// Initialise attributes
QuizManager::QuizManager() : currentQuestionIndex(0), score(0) {
}

// Load questions
void QuizManager::loadQuestions(GameState world) {
    // reset questions, index and score
    questions.clear();
    currentQuestionIndex = 0;
    score = 0;

    // Load questions for different stages
    if (world == GameState::SEAWORLD) {
        loadAmphitriteQuestions();
    }

    // Select 8 random questions
    selectRandomQuestions(8);
    //questionTimer.start();
}

// Amphitrite question bank
void QuizManager::loadAmphitriteQuestions() {
    amphitriteQuestions.clear();
    ifstream file("amphitrite_questions.json");

    if (!file.is_open()) {
        cerr << "Error: Unable to open amphitrite_questions.json" << endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    try {
        for (const auto& item : jsonData["amphitriteQuestions"]) {
            amphitriteQuestions.emplace_back(
                item["question"].get<string>(),
                item["options"].get<vector<string>>(),
                item["correct_answer"].get<int>()
            );
        }
    }
    catch (const json::exception& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
        return;
    }

    // Copy questions to the main question bank
    questions = amphitriteQuestions;
}

// Select a random subset of questions
void QuizManager::selectRandomQuestions(int count) {
    if (questions.size() > count) {
        std::random_device rd;   // Get a random seed
        std::mt19937 rng(rd());  // Seed the random number generator

        // Shuffle all questions
        std::shuffle(questions.begin(), questions.end(), rng);

        // Trim to desired count
        questions.resize(count);
    }
}

// Get the current question
const Question& QuizManager::getCurrentQuestion() const {
    if (currentQuestionIndex >= questions.size()) {
        throw std::out_of_range("No more questions");
    }
    return questions[currentQuestionIndex];
}

// Answer current question and update the score
bool QuizManager::answerCurrentQuestion(int answerIndex) {
    /*
    if (questionTimer.isFinished()) {
        cout << "Timer is up";
        return false;
    }
    */

    if (getCurrentQuestion().isCorrect(answerIndex)) {
        score++;
        return true;
    }
    return false;
}

// Move to the next question
void QuizManager::nextQuestion() {
    currentQuestionIndex++;
    /*
    if (!isQuizComplete()) {
        questionTimer.reset();
        questionTimer.start();
    }
    */
}

bool QuizManager::isQuizComplete() const {
    return currentQuestionIndex >= questions.size();
}

/*
void QuizManager::update(float deltaTime) {
    questionTimer.update(deltaTime);
    if (questionTimer.isFinished()) {

        cout << "Timer fininshed " << endl;
        nextQuestion();
    }
}
*/

int QuizManager::getScore() const { return score; }
int QuizManager::getTotalQuestions() const { return questions.size(); }
int QuizManager::getCurrentQuestionIndex() const { return currentQuestionIndex; }