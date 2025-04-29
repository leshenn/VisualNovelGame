#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Bubble.h"  // Include Bubble class

class BubbleGame {
private:
    sf::RenderWindow window;
    sf::CircleShape shooter;
    sf::Vector2f shooterPos;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Clock gameClock;
    sf::Time elapsedTime;
    float timeLimit = 90.f;
    bool gameOver = false;
    bool BubbleGameWon = false;
    bool gameOver = false;
    sf::Clock gameClock;
    const float timeLimit = 90.0f;

<<<<<<< Updated upstream
    std::vector<Bubble> bubbles;
    std::unique_ptr<Bubble> currentShot = nullptr;
    sf::Vector2f shotVelocity;
    sf::Font font;
=======


    std::vector<Bubble> bubbles;  // Grid or stuck bubbles

    Bubble* currentShot = nullptr;     // The flying bubble
    sf::Vector2f shotVelocity;         // Direction & speed of the shot
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
    bool isGameOver() const { return gameOver; }
=======
	void startGame();
>>>>>>> Stashed changes
};
