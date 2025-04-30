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
        loadHadesQuestions();
    }
    else if (world == GameState::ATLANTIS_QUIZ || world == GameState::SHRINE_QUIZ) {
        questionTimer = 15.f;
        loadPoseidonQuestions();
    }
    else if (world == GameState::KOMOS_QUIZ || world == GameState::FOREST_QUIZ) {
        questionTimer = 15.f;
        loadDionysusQuestions();
    }
    else if (world == GameState::ATHENA_QUIZ) {
        questionTimer = 10.f;
        loadAthenaQuestions();
    }
    else if (world == GameState::APOLLO_QUIZ) {
        questionTimer = 10.f;
        loadApolloQuestions();
    }
    else if (world == GameState::HEPHAESTUS_QUIZ)
    { 
        questionTimer = 10.f;
        loadHephaestusQuestions();
    }

    // Select 8 random questions
    selectRandomQuestions(10);
}


// Hades question bank
void QuizManager::loadHadesQuestions() {
    hadesQuestions.clear();
    ifstream file("hades_questions.json");

    if (!file.is_open()) {
        cerr << "Error: Unable to open hades_questions.json" << endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    try {
        for (const auto& item : jsonData["hadesQuestions"]) {
            hadesQuestions.emplace_back(
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
    questions = hadesQuestions;
}


// Poseidon question bank
void QuizManager::loadPoseidonQuestions() {
    poseidonQuestions.clear();
    ifstream file("poseidon_questions.json");

    if (!file.is_open()) {
        cerr << "Error: Unable to open poseidon_questions.json" << endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    try {
        for (const auto& item : jsonData["poseidonQuestions"]) {
            poseidonQuestions.emplace_back(
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
    questions = poseidonQuestions;
}


// Dionysus question bank
void QuizManager::loadDionysusQuestions() {
    dionysusQuestions.clear();
    ifstream file("dionysus_questions.json");

    if (!file.is_open()) {
        cerr << "Error: Unable to open dionysus_questions.json" << endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    try {
        for (const auto& item : jsonData["dionysusQuestions"]) {
            dionysusQuestions.emplace_back(
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
    questions = dionysusQuestions;
}

// Athena question bank
void QuizManager::loadAthenaQuestions() {
    athenaQuestions.clear();
    ifstream file("athena_questions.json");
    int amountQuestions = 8;

    if (!file.is_open()) {
        cerr << "Error: Unable to open athena_questions.json" << endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    try {
        
        for (const auto& item : jsonData["athenaQuestions"]) {
            athenaQuestions.emplace_back(
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
    questions = athenaQuestions;
}


// Apollo question bank
void QuizManager::loadApolloQuestions() {
    apolloQuestions.clear();
    ifstream file("apollo_questions.json");

    if (!file.is_open()) {
        cerr << "Error: Unable to open apollo_questions.json" << endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    try {
        for (const auto& item : jsonData["apolloQuestions"]) {
            apolloQuestions.emplace_back(
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
    questions = apolloQuestions;
}

// Nemesis question bank
void QuizManager::loadHephaestusQuestions() {
    hephaestusQuestions.clear();
    ifstream file("hephaestus_questions.json");

    if (!file.is_open()) {
        cerr << "Error: Unable to open hephaestus_questions.json" << endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    try {
        for (const auto& item : jsonData["hephaestusQuestions"]) {
            hephaestusQuestions.emplace_back(
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
    questions = hephaestusQuestions;
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