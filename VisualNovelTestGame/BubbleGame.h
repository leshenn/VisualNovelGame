#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class BubbleGame {
private:
    sf::RenderWindow window;
    sf::CircleShape shooter;
    sf::Vector2f shooterPos;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    bool BubbleGameWon = false;
    bool gameOver = false;  // Flag for the game over state

    std::vector<Bubble> bubbles;  // Grid or stuck bubbles
    std::unique_ptr<Bubble> currentShot = nullptr;  // The flying bubble (using unique_ptr)
    sf::Vector2f shotVelocity;  // Direction & speed of the shot

    sf::Clock gameClock;
    const float timeLimit = 90.0f;  // Time limit in seconds
    sf::Font font;  // Font for win/lose messages

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
    bool isGameOver() const { return gameOver; }  // Check if the game is over
};
