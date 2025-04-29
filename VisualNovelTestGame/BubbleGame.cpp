#include "BubbleGame.h"
#include "Bubble.h"

#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

using namespace std;

BubbleGame::BubbleGame()
    : window(sf::VideoMode(800, 600), "Bubble Shooter"), shooterPos(400, 550), timeLimit(90.0f),
    gameOver(false), BubbleGameWon(false), currentShot(nullptr)
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

    // Scale background to fit window
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    float scale = std::max(scaleX, scaleY);
    backgroundSprite.setScale(scale, scale);

    if (!font.loadFromFile("assets/arial.ttf")) {
        cout << "Failed to load font!" << std::endl;
    }

    gameClock.restart();
}

void BubbleGame::spawnBubble(float x, float y, sf::Color color)
{
    bubbles.push_back(Bubble(x, y, 15, color));
}

void BubbleGame::shootBubble()
{
    if (BubbleGameWon || gameOver || currentShot) return;

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f dir(mousePos.x - shooterPos.x, mousePos.y - shooterPos.y);
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length == 0) return;

    dir /= length;
    currentShot = std::make_unique<Bubble>(shooterPos.x + 15, shooterPos.y, 15, shooter.getFillColor());
    shotVelocity = dir * 2.0f;
}

void BubbleGame::setUpBubble()
{
    float radius = 15.0f;
    int rows = 5;
    int cols = 6;
    float bubbleSpacing = radius * 2;
    float totalWidth = cols * bubbleSpacing;
    float startX = (800 - totalWidth) / 2.0f;
    float startY = 50.0f;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = startX + col * bubbleSpacing;
            float y = startY + row * bubbleSpacing;
            if (row % 2 == 1) x += radius;
            bubbles.push_back(Bubble(x, y, radius, randomColor()));
        }
    }
}

void BubbleGame::update()
{
    if (gameOver || BubbleGameWon) return;

    float elapsedTime = gameClock.getElapsedTime().asSeconds();
    if (elapsedTime >= timeLimit) {
        gameOver = true;
        return;
    }

    if (currentShot) {
        currentShot->shape.move(shotVelocity);
        sf::Vector2f pos = currentShot->shape.getPosition();

        if (pos.x <= 0 || pos.x + currentShot->shape.getRadius() * 2 >= 800) {
            shotVelocity.x = -shotVelocity.x;
        }

        if (pos.y < 0) {
            currentShot.reset();
            shooter.setFillColor(randomColor());
            return;
        }

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
                    bubbles.push_back(*currentShot);
                }

                currentShot.reset();
                shooter.setFillColor(randomColor());
                return;
            }
        }
    }

    if (bubbles.empty() && !BubbleGameWon) {
        BubbleGameWon = true;
    }
}

void BubbleGame::setUpLevel()
{
    float radius = 15.f;
    float diameter = radius * 2;
    int rows = 5;
    int cols = 12;
    float totalWidth = cols * diameter;
    float totalHeight = rows * diameter;
    float startX = (800 - totalWidth) / 2.0f;
    float startY = (600 - totalHeight) / 2.0f;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = startX + col * diameter;
            float y = startY + row * diameter;
            if (row % 2 == 1) x += radius;
            spawnBubble(x, y, randomColor());
        }
    }
}

void BubbleGame::render()
{
    window.clear();
    window.draw(backgroundSprite);
    window.draw(shooter);

    for (auto& bubble : bubbles) {
        bubble.render(window);
    }

    if (currentShot) {
        currentShot->render(window);
    }

    sf::Vertex line[] = {
        sf::Vertex(shooterPos + sf::Vector2f(15, 15), sf::Color::White),
        sf::Vertex((sf::Vector2f)sf::Mouse::getPosition(window), sf::Color::White)
    };
    window.draw(line, 2, sf::Lines);

    // Draw win or lose message
    sf::Text message;
    message.setFont(font);
    message.setCharacterSize(50);
    message.setStyle(sf::Text::Bold);
    message.setPosition(300, 250);

    if (BubbleGameWon) {
        message.setString("You Win!");
        message.setFillColor(sf::Color::Green);
        window.draw(message);
    }
    else if (gameOver) {
        message.setString("You Lose!");
        message.setFillColor(sf::Color::Red);
        window.draw(message);
    }

    window.display();
}

void BubbleGame::handling()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            shootBubble();
        }
    }
}

bool BubbleGame::isRunning()
{
    return window.isOpen();
}

void BubbleGame::popMatchingBubbles(size_t index)
{
    if (index >= bubbles.size()) return;

    sf::Color targetColor = bubbles[index].color;
    std::vector<size_t> toCheck = { index };
    std::vector<size_t> toPop;

    while (!toCheck.empty()) {
        size_t current = toCheck.back();
        toCheck.pop_back();

        if (std::find(toPop.begin(), toPop.end(), current) != toPop.end())
            continue;

        toPop.push_back(current);

        sf::Vector2f pos1 = bubbles[current].shape.getPosition();

        for (size_t i = 0; i < bubbles.size(); ++i) {
            if (i == current) continue;
            if (std::find(toPop.begin(), toPop.end(), i) != toPop.end()) continue;

            sf::Vector2f pos2 = bubbles[i].shape.getPosition();
            float dist = std::hypot(pos1.x - pos2.x, pos1.y - pos2.y);

            if (dist <= 30.0f && bubbles[i].color == targetColor) {
                toCheck.push_back(i);
            }
        }
    }

    for (auto i : toPop) {
        bubbles[i].isActive = false;
    }

    bubbles.erase(std::remove_if(bubbles.begin(), bubbles.end(),
        [](const Bubble& b) { return !b.isActive; }), bubbles.end());
}

sf::Color BubbleGame::randomColor()
{
    int r = rand() % 3;
    switch (r) {
    case 0: return sf::Color::White;
    case 1: return sf::Color::Magenta;
    case 2: return sf::Color::Yellow;
    }
    return sf::Color::White;
}

void BubbleGame::startGame()
{
	gameClock.restart();
}
