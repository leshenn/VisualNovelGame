#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include "RhythmGame.h"

RhythmGame::RhythmGame()
    : window(sf::VideoMode(1920, 1080), "Rhythm Game", sf::Style::Fullscreen)
    , spawnTimer(0.0f)
    , spawnInterval(1.5f)
    , speedMultiplier(1.0f)
    , speedIncreaseTimer(0.0f)
    , score(0)
    , feedbackTimer(0.0f)
    , spawnPositions{ 810, 910, 1010, 1110 }
    , keybinds{ sf::Keyboard::Left, sf::Keyboard::Down, sf::Keyboard::Up, sf::Keyboard::Right }
{
    initializeBackground();
    initializeArrows();
    initializeUI();
    initializeSounds();
    initializeHealthBar();
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

RhythmGame::~RhythmGame() {  
   for (auto* img : fallingImages) delete img;  
}

void RhythmGame::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void RhythmGame::initializeBackground() {
    loadAndScaleTexture(fullBackgroundTexture, fullBackground,
        "RhythmAssets/Minigame/RhythmBackground.png", fullBackgroundSize);
}

void RhythmGame::loadAndScaleTexture(sf::Texture& texture, sf::Sprite& sprite,
    const std::string& filename, const sf::Vector2f& targetSize)
{
    if (!texture.loadFromFile(filename)) std::cerr << "Failed to load texture: " << filename << std::endl;
    sprite.setTexture(texture);
    sf::Vector2u ts = texture.getSize();
    sprite.setScale(targetSize.x / ts.x, targetSize.y / ts.y);
}

void RhythmGame::initializeArrows() {
    keyToDirection = {
        { sf::Keyboard::Left,  "left"  },
        { sf::Keyboard::Down,  "down"  },
        { sf::Keyboard::Up,    "up"    },
        { sf::Keyboard::Right, "right" }
    };
    for (auto& [key, dir] : keyToDirection) {
        sf::Texture tex;
        std::string fn = "RhythmAssets/Minigame/Entities/arrow_" + dir + ".png";
        if (!tex.loadFromFile(fn)) std::cerr << "Failed to load arrow: " << fn << std::endl;
        arrowTextures["arrow_" + dir] = tex;
    }
}

int RhythmGame::getScore(){return score;}

void RhythmGame::initializeUI() {
    robotoFont.loadFromFile("RhythmAssets/Font/fnf.ttf");
    fnfFont.loadFromFile("RhythmAssets/Font/fnf.ttf");

    scoreText.setFont(robotoFont);
    scoreText.setCharacterSize(36);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 60.f);

    feedbackText.setFont(fnfFont);
    feedbackText.setCharacterSize(72);
    feedbackText.setFillColor(sf::Color::Red);
    feedbackText.setPosition(1400.f, 100.f);

    gameOverText.setFont(fnfFont);
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(675.f, 400.f);

    detectionZone.setSize(bottomBackgroundSize);
    detectionZone.setFillColor(sf::Color(0, 0, 255, 100));
    detectionZone.setPosition(0.f, 1080.f - bottomBackgroundSize.y);
}

void RhythmGame::initializeSounds() {
    hitBuffer.loadFromFile("RhythmAssets/Sounds/hit_sound.wav");
    hitSound.setBuffer(hitBuffer);
    missBuffer.loadFromFile("RhythmAssets/Sounds/miss_sound.wav");
    missSound.setBuffer(missBuffer);
}

void RhythmGame::initializeHealthBar() {
    healthBarTexture.loadFromFile("RhythmAssets/Minigame/Entities/HealthBar.png");
    healthBarSprite.setTexture(healthBarTexture);
    healthBarSprite.setPosition(healthBarPosition);
    auto ts = healthBarTexture.getSize();
    healthBarSprite.setScale(healthBarSize.x / ts.x, healthBarSize.y / ts.y);

    //healthFill.setSize({healthBarSize.x-50, healthBarSize.y-50});
    healthFill.setFillColor(sf::Color::Red);
    healthFill.setPosition(healthBarPosition.x,healthBarPosition.y);
}

void RhythmGame::handleEvents() {
    sf::Event ev;
    while (window.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed) window.close();
    }
}

void RhythmGame::update() {
    // On Game Over, await F to close

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && isGameOver) window.close();
    if (isGameOver && endScreen.asSeconds()<=0) {
        window.close();
    }
    float dt = clock.restart().asSeconds();
    if (isGameOver) {
        endScreen -= sf::seconds(dt);
		return;
    }
    spawnTimer += dt;
    speedIncreaseTimer += dt;
    feedbackTimer -= dt;

    if (speedIncreaseTimer >= ScalingRate) {
        spawnInterval = std::max(0.3f, spawnInterval - 0.05f);
        speedMultiplier += 0.1f;
        speedIncreaseTimer = 0.f;
    }
    if (spawnTimer >= spawnInterval) {
        spawnFallingImage();
        spawnTimer = 0.f;
    }

    float moveAmt = baseSpeed * speedMultiplier * dt;
    for (auto* img : fallingImages) img->sprite.move(0, moveAmt);

    for (auto it = fallingImages.begin(); it != fallingImages.end();) {
        auto* img = *it;
        if (img->sprite.getPosition().y > window.getSize().y) {
            delete img;
            it = fallingImages.erase(it);
            feedbackText.setString("MISS!");
            feedbackText.setFillColor(sf::Color::Red);
            feedbackTimer = 1.f;
            missSound.play();
            if (--health <= 0) {
                health = 0;
                isGameOver = true;
            }
        }
        else ++it;
    }
    for (auto key : keybinds) if (sf::Keyboard::isKeyPressed(key)) checkKeyPress(key);

    // Update health fill width
    float totalPadX = 10.f;  // 5px on left + 5px on right
    float fillableW = healthBarSize.x - totalPadX;

    // 2) compute fraction [0..1] and actual width
    float pct = std::max(0.f, std::min(1.f, static_cast<float>(health) / static_cast<float>(maxHealth)));
    float w = fillableW * pct;

    // 3) apply size (height minus 10px for vertical padding) and reposition
    healthFill.setSize({ w, healthBarSize.y - 10 });
    healthFill.setPosition(healthBarPosition.x + 25,healthBarPosition.y + 5);
}

void RhythmGame::render() {
    window.clear();
    window.draw(fullBackground);
    for (auto* img : fallingImages) window.draw(img->sprite);
    //window.draw(detectionZone);

    window.draw(healthFill);
    window.draw(healthBarSprite);

    scoreText.setString("Score: " + std::to_string(score));
    window.draw(scoreText);
    if (feedbackTimer > 0) window.draw(feedbackText);

    if (isGameOver) window.draw(gameOverText);

    window.display();
}

void RhythmGame::spawnFallingImage() {
    auto* img = new FallingImage;
    int idx = std::rand() % 4;
    img->keybind = keybinds[idx];
    std::string dir = keyToDirection[img->keybind];
    auto& tex = arrowTextures["arrow_" + dir];
    img->sprite.setTexture(tex);
    auto ts = tex.getSize();
    img->sprite.setScale(arrowSize.x / ts.x, arrowSize.y / ts.y);
    img->sprite.setOrigin(ts.x / 2.f, ts.y / 2.f);
    img->sprite.setPosition(spawnPositions[idx], -arrowSize.y);
    fallingImages.push_back(img);
}

void RhythmGame::checkKeyPress(sf::Keyboard::Key key) {
    for (auto it = fallingImages.begin(); it != fallingImages.end();) {
        auto* img = *it;
        if (img->keybind == key && img->sprite.getGlobalBounds().intersects(detectionZone.getGlobalBounds())) {
            delete img;
            it = fallingImages.erase(it);
            score++;
            feedbackText.setString("HIT!");
            feedbackText.setFillColor(sf::Color::Green);
            feedbackTimer = 1.f;
            hitSound.play();
        }
        else ++it;
    }
}

