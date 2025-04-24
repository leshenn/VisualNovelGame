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
    if (world == GameState::UNDERWORLD) {
        loadHadesQuestions();
    }
    else if (world == GameState::SEAWORLD) {
        loadPoseidonQuestions();
    }
    else if (world == GameState::COUNTRY_SIDE) {
        loadDionysusQuestions();
    }
    else if (world == GameState::ATHENS) {
        loadAthenaQuestions();
    }
    else if (world == GameState::DELPHI) {
        loadApolloQuestions();
    }
    else if (world == GameState::RHAMNOUS)
    { 
        loadNemesisQuestions();
    }
    else if (world == GameState::THRACE)
    {
        loadAresQuestions();
    }
    else if (world == GameState::CRETE) {
        loadDaedalusQuestions();
    }
    else if (world == GameState::CYPRUS)
    {
        loadAproditeQuestions();
    }
    else if (world == GameState::OLYMPUS) {
        loadZeusQuestions();
    }
    else if (world == GameState::LETHE) {
        loadHypnosQuestions();
    }
    else if (world == GameState::MOUNT_CYLLENE) {
        loadHermesQuestions();
    }
    else if (world == GameState::ARGOS) {
        loadHeraQuestions();
    }

    // Select 8 random questions
    selectRandomQuestions(10);
    questionTimer.start();
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
void QuizManager::loadNemesisQuestions() {
    nemesisQuestions.clear();
    ifstream file("nemesis_questions.json");

    if (!file.is_open()) {
        cerr << "Error: Unable to open hades_questions.json" << endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    try {
        for (const auto& item : jsonData["nemesisQuestions"]) {
            nemesisQuestions.emplace_back(
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
    questions = nemesisQuestions;
}

// Ares question bank
void QuizManager::loadAresQuestions() {
    aresQuestions.clear();
    ifstream file("ares_questions.json");

    if (!file.is_open()) {
        cerr << "Error: Unable to open ares_questions.json" << endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    try {
        for (const auto& item : jsonData["aresQuestions"]) {
            aresQuestions.emplace_back(
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
    questions = aresQuestions;
}


// Daedalus question bank
void QuizManager::loadDaedalusQuestions() {
    daedalusQuestions.clear();
    ifstream file("daedalus_questions.json");

    if (!file.is_open()) {
        cerr << "Error: Unable to open daedalus_questions.json" << endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    try {
        for (const auto& item : jsonData["daedalusQuestions"]) {
            daedalusQuestions.emplace_back(
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
    questions = daedalusQuestions;
}

// aphrodite question bank
void QuizManager::loadAproditeQuestions() {
    aphroditeQuestions.clear();
    ifstream file("aphrodite_questions.json");

    if (!file.is_open()) {
        cerr << "Error: Unable to open aphrodite_questions.json" << endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    try {
        for (const auto& item : jsonData["aphroditeQuestions"]) {
            aphroditeQuestions.emplace_back(
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
    questions = aphroditeQuestions;
}

// zeus question bank
void QuizManager::loadZeusQuestions() {
    zeusQuestions.clear();
    ifstream file("zeus_questions.json");

    if (!file.is_open()) {
        cerr << "Error: Unable to open zeus_questions.json" << endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    try {
        for (const auto& item : jsonData["zeusQuestions"]) {
            zeusQuestions.emplace_back(
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
    questions = zeusQuestions;
}

void QuizManager::loadHypnosQuestions() {
    hypnosQuestions.clear();
    ifstream file("hypnos_questions.json");

    if (!file.is_open()) {
        cerr << "Error: Unable to open hypnos_questions.json" << endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    try {
        for (const auto& item : jsonData["hypnosQuestions"]) {
            hypnosQuestions.emplace_back(
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
    questions = hypnosQuestions;
}

// hermes question bank
void QuizManager::loadHermesQuestions() {
    hermesQuestions.clear();
    ifstream file("hermes_questions.json");

    if (!file.is_open()) {
        cerr << "Error: Unable to open hermes_questions.json" << endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    try {
        for (const auto& item : jsonData["hermesQuestions"]) {
            hermesQuestions.emplace_back(
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
    questions = hermesQuestions;
}

// hera question bank
void QuizManager::loadHeraQuestions() {
    heraQuestions.clear();
    ifstream file("hera_questions.json");

    if (!file.is_open()) {
        cerr << "Error: Unable to open hera_questions.json" << endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    try {
        for (const auto& item : jsonData["heraQuestions"]) {
            heraQuestions.emplace_back(
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
    questions = heraQuestions;
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
    
    if (questionTimer.isFinished()) {
        cout << "Timer is up";
        return false;
    }
    

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
    
    if (!isQuizComplete()) {
        questionTimer.reset();
        questionTimer.start();
    }
    else {
        questionTimer.stop();
    }
    
}

bool QuizManager::isQuizComplete() const {
    return quizComplete;
}


void QuizManager::update(float deltaTime) {
    questionTimer.update(deltaTime);
    if (questionTimer.isFinished()) {

        cout << "Timer fininshed " << endl;
        nextQuestion();
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