#include "BubbleGame.h"
#include "Bubble.h"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

BubbleGame::BubbleGame()
    : window(sf::VideoMode(800, 600), "Bubble Shooter"), shooterPos(400, 550)
{
    shooter.setRadius(15);
    shooter.setFillColor(sf::Color::Red);
    shooter.setPosition(shooterPos);
    setUpLevel();
    shooter.setFillColor(randomColor());
    setUpBubble();

    if (!backgroundTexture.loadFromFile("BubbleAssets/BBGame.jpg")) {
        cout << "Failed to load background image!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Scale to window size and preserve aspect ratio
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    float scale = std::max(scaleX, scaleY);  // To preserve aspect ratio

    backgroundSprite.setScale(scale, scale);

    // Load the font once for win/lose messages
    if (!font.loadFromFile("assets/arial.ttf")) {
        cout << "Failed to load font!" << std::endl;
    }
}

void BubbleGame::spawnBubble(float x, float y, sf::Color color)
{
    bubbles.push_back(Bubble(x, y, 15, color));
}

void BubbleGame::shootBubble()
{
    if (BubbleGameWon || gameOver) return;  // Don't allow shooting if the game is won or over

    if (currentShot != nullptr) return;  // Only one bubble can be in the air

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f dir(mousePos.x - shooterPos.x, mousePos.y - shooterPos.y);
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (length == 0) return;  // Avoid division by zero
    dir /= length;

    currentShot = std::make_unique<Bubble>(shooterPos.x + 15, shooterPos.y, 15, shooter.getFillColor());
    shotVelocity = dir * 2.0f;  // Set speed
}

void BubbleGame::setUpBubble()
{
    float radius = 15.0f;
    int rows = 5;
    int cols = 6;

    float bubbleSpacing = radius * 2;
    float totalWidth = cols * bubbleSpacing;
    float startX = (800 - totalWidth) / 2.0f;  // Center the grid
    float startY = 50.0f;  // Starting near top

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = startX + col * bubbleSpacing;
            float y = startY + row * bubbleSpacing;

            // Offset every other row to form a triangle pattern
            if (row % 2 == 1) x += radius;

            bubbles.push_back(Bubble(x, y, radius, randomColor()));
        }
    }
}

void BubbleGame::update()
{
    if (gameOver || BubbleGameWon) return;  // Don't update if the game is over or won

    // Check if 90 seconds have passed
    float elapsedTime = gameClock.getElapsedTime().asSeconds();
    if (elapsedTime >= timeLimit) {
        gameOver = true;  // Mark the game as over
    }

    if (currentShot) {
        currentShot->shape.move(shotVelocity);  // Move the bubble

        sf::Vector2f pos = currentShot->shape.getPosition();

        // Wall bounce logic
        if (pos.x <= 0 || pos.x + currentShot->shape.getRadius() * 2 >= 800) {
            shotVelocity.x = -shotVelocity.x;  // Reverse the X velocity on collision
        }

        // Top of screen = miss
        if (pos.y < 0) {
            currentShot.reset();  // Clear current shot using unique_ptr
            shooter.setFillColor(randomColor());
            return;
        }

        // Collision with bubbles
        for (size_t i = 0; i < bubbles.size(); ++i) {
            float dist = std::hypot(
                pos.x - bubbles[i].shape.getPosition().x,
                pos.y - bubbles[i].shape.getPosition().y
            );

            if (dist <= 30.0f) {
                if (currentShot->color == bubbles[i].color) {
                    popMatchingBubbles(i);
                }
                else {
                    bubbles.push_back(*currentShot);  // Add to bubbles if they don't match
                }

                currentShot.reset();  // Clear current shot using unique_ptr
                shooter.setFillColor(randomColor());
                return;
            }
        }
    }

    // If no more bubbles, player wins
    if (bubbles.empty() && !BubbleGameWon) {
        BubbleGameWon = true;
    }
}

void BubbleGame::render()
{
    window.clear();

    window.draw(backgroundSprite);  // Draw the background first
    window.draw(shooter);  // Draw the shooter

    for (auto& bubble : bubbles) {
        bubble.render(window);  // Draw bubbles
    }

    if (currentShot) {
        currentShot->render(window);  // Draw the flying bubble
    }

    // Aiming line
    sf::Vertex line[] =
    {
        sf::Vertex(shooterPos + sf::Vector2f(15, 15), sf::Color::White),
        sf::Vertex((sf::Vector2f)sf::Mouse::getPosition(window), sf::Color::White)
    };
    window.draw(line, 2, sf::Lines);

    // Draw win message
    if (BubbleGameWon) {
        sf::Text winText("You Win!", font, 50);
        winText.setFillColor(sf::Color::Green);
        winText.setStyle(sf::Text::Bold);
        winText.setPosition(800 / 2 - 100, 600 / 2 - 50);
        window.draw(winText);
    }

    // Draw lose message if the game is lost
    if (gameOver) {
        sf::Text loseText("You Lose!", font, 50);
        loseText.setFillColor(sf::Color::Red);
        loseText.setStyle(sf::Text::Bold);
    }