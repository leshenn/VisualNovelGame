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
QuizManager::QuizManager() : currentQuestionIndex(0), score(0) ,questionTimer(10.0f){
}

// Load questions
void QuizManager::loadQuestions(GameState world) {

    // reset questions, index and score
    questions.clear();
    currentQuestionIndex = 0;
    score = 0;

    // Load questions for different stages
    if (world == GameState::HADES_QUIZ) {
        questionTimer = 15.f;
        loadQuestions("hades_questions.json", "hadesQuestions");
    }
    else if (world == GameState::ATLANTIS_QUIZ || world == GameState::SHRINE_QUIZ) {
        questionTimer = 15.f;
        loadQuestions("poseidon_questions.json", "poseidonQuestions");
    }
    else if (world == GameState::KOMOS_QUIZ || world == GameState::FOREST_QUIZ) {
        questionTimer = 15.f;
        loadQuestions("dionysus_questions.json", "dionysusQuestions");
    }
    else if (world == GameState::ATHENA_QUIZ) {
        questionTimer = 10.f;
        loadQuestions("athena_questions.json", "athenaQuestions");
    }
    else if (world == GameState::APOLLO_QUIZ) {
        questionTimer = 10.f;
        loadQuestions("apollo_questions.json", "apolloQuestions");
    }
    else if (world == GameState::HEPHAESTUS_QUIZ)
    { 
        questionTimer = 10.f;
        loadQuestions("hephaestus_questions.json", "hephaestusQuestions");
    }

    // Select 8 random questions
    selectRandomQuestions(10);
}

// Load quiz questions
void QuizManager::loadQuestions(string jsonName, string title) {
    quizQuestions.clear();
    ifstream file(jsonName);

    if (!file.is_open()) {
        cerr << "Error: Unable to open json file." << endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    try {
        for (const auto& item : jsonData[title]) {
            quizQuestions.emplace_back(
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
    questions = quizQuestions;
}

// Select a random subset of questions
void QuizManager::selectRandomQuestions(int count) {
    
    std::random_device rd;   // Get a random seed
    std::mt19937 rng(rd());  // Seed the random number generator

    // Shuffle all questions
    std::shuffle(questions.begin(), questions.end(), rng);

    // Trim to desired count
    questions.resize(count);

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
    
    if (getCurrentQuestion().isCorrect(answerIndex)) {
        score++;
        return true;
    }
    return false;
}

// Move to the next question
void QuizManager::nextQuestion() {
    currentQuestionIndex++;

    if (currentQuestionIndex >= questions.size()) {
        quizComplete = true; // Set completion flag
    }  
}

bool QuizManager::isQuizComplete() const {
    return quizComplete;
}


void QuizManager::update(float deltaTime) {
    questionTimer.update(deltaTime);
    if (questionTimer.isFinished()) {
        cout << "Timer fininshed " << endl;
        questionTimer.stop();
    }
}

int QuizManager::getScore() const { return score; }
int QuizManager::getTotalQuestions() const { return questions.size(); }
int QuizManager::getCurrentQuestionIndex() const { return currentQuestionIndex; }

void QuizManager::reset() {
    currentQuestionIndex = 0;
    score = 0;
    questions.clear();
    quizComplete = false; // Add this
    questionTimer.reset();
}