#pragma once

#include <SFML/Graphics.hpp>
<<<<<<< HEAD
#include <memory>
#include <vector>
#include "Bubble.h"  // Include Bubble class
=======
#include <vector>
#include "Bubble.h"
>>>>>>> main

class BubbleGame {
private:
    sf::RenderWindow window;
    sf::CircleShape shooter;
    sf::Vector2f shooterPos;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    bool BubbleGameWon = false;
<<<<<<< HEAD
    bool gameOver = false;
    sf::Clock gameClock;
    const float timeLimit = 90.0f;

    std::vector<Bubble> bubbles;
    std::unique_ptr<Bubble> currentShot = nullptr;
    sf::Vector2f shotVelocity;
    sf::Font font;
=======


    std::vector<Bubble> bubbles;  // Grid or stuck bubbles

    Bubble* currentShot = nullptr;     // The flying bubble
    sf::Vector2f shotVelocity;         // Direction & speed of the shot
>>>>>>> main

public:
    BubbleGame();
    void spawnBubble(float x, float y, sf::Color color);
    void shootBubble();
    void setUpBubble();
    void update();
    void render();
    void handling();
    bool isRunning();
    void setUpLevel();
    void popMatchingBubbles(size_t index);
    sf::Color randomColor();
<<<<<<< HEAD
    bool isGameOver() const { return gameOver; }
=======
>>>>>>> main
};
