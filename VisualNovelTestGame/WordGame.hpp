#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>
#include <array>
#include <set>
#include <random>
#include <stdexcept>
struct Word {
    std::string text;
    int gridIndex;
    bool highlighted;
};

class WordGame {
public:
    WordGame();
    void run();
    int getFinalScore();
    bool getGameOver();
private:
    // Private member functions
    void handleEvents();
    void update();
    void render();
    void spawnWord();
    void handleInput(char c);
    void resetInput();
    void wrongInput();
    void drawSpeedBar();
    std::string generateWord();

    // Member variables
    const float MAX_SPAWN_INTERVAL;
    float spawnInterval;
    const float minSpawnInterval;
    const float spawnAcceleration;
    float speed;
    sf::RenderWindow window;
    sf::Font font;
    sf::SoundBuffer correctBuffer;
    sf::Sound correctSound;
    sf::SoundBuffer wrongBuffer;
    sf::Sound wrongSound;
    std::vector<Word> activeWords;
    std::array<bool, 9> gridCells;
    sf::Clock spawnClock;
    std::string currentInput;
    char targetStartChar;
    int score;
    bool gameOver;
    int errorGridIndex;
    sf::Clock errorTimer;
    const float ERROR_DURATION;
    std::vector<std::string> wordList;
    sf::Time endScreen;
};