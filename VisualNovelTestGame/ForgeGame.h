#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>

// Define the Hotspot and Particle structs
struct Hotspot {
    sf::Sprite sprite;
    bool isVisible;
    float activeTime;
    sf::Vector2f position; // Store original position for oscillation
};

struct Particle {
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float lifetime;
};

class ForgeGame {
public:
    // Constructor
    ForgeGame();

    // Destructor
    ~ForgeGame();

    // Main game loop method
    void run();
    int getScore();

private:
    // Window
    sf::RenderWindow window;

    // Game State
    int score;
    int activeHotspots;
    const int maxHotspots = 10; // Max visible hotspots at any time
    float heatLevel; // 0-100%
    float coolingRate; // Heat loss per second
    bool gameOver;

    // Difficulty / Spawn Timing
    float baseSpawnTime;
    float minSpawnTime;
    float spawnTimeDecrease;
    float currentSpawnTime;
    float difficultyTimer; // Timer to track when to decrease spawn time

    // Game Objects
    sf::Sprite background;
    sf::RectangleShape swordBlade;
    sf::RectangleShape topVice;
    sf::RectangleShape bottomVice;
    sf::ConvexShape swordPoint;
    sf::RectangleShape swordHandle; 
    sf::Sprite hammer;

    // Resources
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Texture hammerTexture;
    sf::Texture hotspotTexture;
    sf::SoundBuffer hitBuffer;
    sf::Sound hitSound;
    sf::Music forgeMusic;

    // Hotspots
    std::vector<Hotspot> hotspots;
    const int maxActiveHotspots = 10; // Same as maxHotspots for game logic

    // Particles
    std::vector<Particle> particles;
    const float particleLifetime = 0.5f; // Base lifetime for particles

    // Timers
    sf::Clock clock;
    float hotspotTimer; // Timer for spawning new hotspots

    // UI Elements
    sf::Text scoreText;
    sf::Text heatText;
    sf::Text hotspotText;
    sf::Text gameOverText;

    // Hammer state for animation
    float hammerRotation;
    sf::Vector2f lastMousePos; 

    // Private Helper Methods
    void initWindow();
    void initResources();
    void initGameObjects();
    void initUI();

    void processEvents();
    void update(float deltaTime);
    void render();

    // Update helpers
    void updateDifficulty(float deltaTime);
    void updateHeat(float deltaTime);
    void updateHotspots(float deltaTime);
    void updateParticles(float deltaTime);
    void updateUI();
    void updateHammer(); // Update hammer rotation/position

    // Rendering helpers (optional, could be in render)
    void renderBackground();
    void renderSword();
    void renderHotspots();
    void renderParticles();
    void renderUI();
    void renderHammer();

    // Game logic helpers
    void CreateSparks(sf::Vector2f position, int count = 15);
    void handleMouseClick(sf::Vector2f mousePos);
    void checkGameOverConditions();
};
