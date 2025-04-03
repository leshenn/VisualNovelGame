#include "QuizManager.h"
#include "GameState.h"
#include <stdexcept>
#include <algorithm>

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
    if (world == GameState::AMPHITRITE_STAGE) {
        loadAmphitriteQuestions();
    }

    // Select 8 random questions
    selectRandomQuestions(8);
}

// Amphitrite question bank
void QuizManager::loadAmphitriteQuestions() {
    amphitriteQuestions = {
        Question("Who is Amphitrite married to?",
            { "A) Poseidon", "B) Zeus", "C) Apollo", "D) Hades" }, 0),
        Question("What is Amphitrite's role in Greek mythology?",
            { "A) Goddess of the harvest", "B) Goddess of wisdom", "C) Goddess of the sea", "D) Goddess of love" }, 2),
        Question("What symbol is often associated with Amphitrite?",
            { "A) Dolphin", "B) Owl", "C) Lyre", "D) Laurel wreath" }, 0),
        Question("Who is the son of Amphitrite and Poseidon?",
            { "A) Theseus", "B) Triton", "C) Perseus", "D) Achilles" }, 1),
        Question("Which of the following creatures is Amphitrite sometimes depicted riding?",
            { "A) Chariot drawn by horses", "B) Dolphin", "C) Lion", "D) Pegasus" }, 1),
        Question("What type of deity is Amphitrite?",
            { "A) Titan", "B) Primordial", "C) Olympian", "D) Nymph" }, 2),
        Question("Where was Amphitrite born?",
            { "A) Mount Olympus", "B) The Aegean Sea", "C) The Ocean", "D) Atlantis" }, 2),
        Question("What is the name of Amphitrite's father?",
            { "A) Oceanus", "B) Cronus", "C) Atlas", "D) Zeus" }, 0),
        Question("Which of the following is a famous myth involving Amphitrite?",
            { "A) The Trojan War", "B) The creation of the first storm", "C) Her refusal of Poseidon's proposal", "D) The battle with Typhon" }, 2),
        Question("What was Amphitrite's initial reaction when Poseidon courted her?",
            { "A) She accepted immediately", "B) She fled to the ends of the Earth", "C) She demanded a grand gift", "D) She challenged Poseidon to a duel" }, 1),
        Question("What sea creature does Amphitrite have as a companion?",
            { "A) Whale", "B) Turtle", "C) Sea serpent", "D) Dolphin" }, 3),
        Question("What power does Amphitrite hold as the goddess of the sea?",
            { "A) Control over winds", "B) Command over storms and tides", "C) Ability to heal the sick", "D) Control of the earth's fertility" }, 1),
        Question("What is Amphitrite's relationship with the other sea gods?",
            { "A) She is their ruler", "B) She is indifferent to them", "C) She is their rival", "D) She is their mother" }, 0),
        Question("What form of animal is Amphitrite sometimes depicted as?",
            { "A) A giant octopus", "B) A fish-tailed woman", "C) A giant eagle", "D) A mermaid" }, 1),
        Question("What is the Greek term for Amphitrite's role as a goddess of the sea?",
            { "A) Thalassa", "B) Nereid", "C) Thalassion", "D) Oceanis" }, 3),
        Question("Which of the following gods was Amphitrite's rival for Poseidon's affections?",
            { "A) Hera", "B) Demeter", "C) Thetis", "D) Medusa" }, 2),
        Question("How is Amphitrite often represented in art?",
            { "A) As a fully human woman", "B) As a woman with the lower body of a fish", "C) With wings and a golden crown", "D) As a creature with the body of a lion" }, 1),
        Question("What does Amphitrite's name mean in Greek?",
            { "A) 'Queen of the ocean'", "B) 'Sea goddess'", "C) 'She who encircles the world'", "D) 'Protector of the deep'" }, 2),
        Question("Who helped Poseidon find Amphitrite when she fled?",
            { "A) Zeus", "B) Hermes", "C) Delphinus, a dolphin", "D) Athena" }, 2),
        Question("What was the outcome of Amphitrite's marriage to Poseidon?",
            { "A) They had no children", "B) They ruled over the oceans and seas together", "C) She left him for another god", "D) They created the first hurricane" }, 1)
    };
    // Copy to questions
    questions = amphitriteQuestions;
}

// Select a random subset of questions
void QuizManager::selectRandomQuestions(int count) {

    if (questions.size() > count) {
        // Shuffle all questions
        std::random_shuffle(questions.begin(), questions.end());

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
    if (getCurrentQuestion().isCorrect(answerIndex)) {
        score++;
        return true;
    }
    return false;
}

// Move to the next question
void QuizManager::nextQuestion() {
    currentQuestionIndex++;
}

bool QuizManager::isQuizComplete() const {
    return currentQuestionIndex >= questions.size();
}

int QuizManager::getScore() const { return score; }
int QuizManager::getTotalQuestions() const { return questions.size(); }
int QuizManager::getCurrentQuestionIndex() const { return currentQuestionIndex; }