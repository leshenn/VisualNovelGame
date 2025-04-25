#pragma once

#include "RhythmGame.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>


class RhythmGame
{
private:

struct FallingImage {
    sf::Sprite sprite;
    sf::Keyboard::Key keybind;
};
    // Window and background
    sf::RenderWindow window;
    sf::Texture fullBackgroundTexture;
    sf::Sprite fullBackground;

    // Game elements
    std::map<std::string, sf::Texture> arrowTextures;
    std::vector<FallingImage*> fallingImages;
    float spawnTimer;
    float spawnInterval;
    float speedMultiplier;
    int score;
    sf::Font robotoFont;
    sf::Font fnfFont;
    sf::Text scoreText;
    sf::Text feedbackText;
    sf::Text gameOverText;
    float feedbackTimer;
    sf::RectangleShape detectionZone;

    // Timing and scaling
    float speedIncreaseTimer;
    const float ScalingRate = 0.5f;
    const float baseSpeed = 200.0f;
	sf::Time endScreen = sf::seconds(3);

    // Positions and mappings
    std::vector<float> spawnPositions;
    std::vector<sf::Keyboard::Key> keybinds;
    std::map<sf::Keyboard::Key, std::string> keyToDirection;

    // Sizes
    const sf::Vector2f fullBackgroundSize{ 1920,1080 };
    const sf::Vector2f arrowSize{ 100,100 };
    const sf::Vector2f bottomBackgroundSize{ 1920,150 };

    sf::Clock clock;

    // Sound effects
    sf::SoundBuffer hitBuffer;
    sf::SoundBuffer missBuffer;
    sf::Sound hitSound;
    sf::Sound missSound;

    // Health bar
    int health = 15;
    const int maxHealth = 15;
    sf::Texture healthBarTexture;
    sf::Sprite healthBarSprite;
    sf::RectangleShape healthFill;
    sf::Vector2f healthBarSize = { 300.f, 30.f };
    sf::Vector2f healthBarPosition = { 30.f, 30.f };

    // Game state
    bool isGameOver = false;

public:
    void run();
 
     RhythmGame();
     ~RhythmGame();

 
private:
    void initializeBackground();
    void loadAndScaleTexture(sf::Texture& texture, sf::Sprite& sprite,
        const std::string& filename, const sf::Vector2f& targetSize);
    void initializeArrows();
    void initializeUI();
    void initializeSounds();
    void initializeHealthBar();

    // Core gameplay functions
    void handleEvents();
    void update();
    void render();
    void spawnFallingImage();
    void checkKeyPress(sf::Keyboard::Key key);


};

