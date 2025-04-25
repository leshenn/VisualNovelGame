#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

class Bubble
{
public:
    sf::CircleShape shape;
    sf::Color color;
    bool isActive;

    Bubble(float x, float y, float radius, sf::Color color)
        : color(color)
    {
        shape.setRadius(radius);
        shape.setFillColor(color);
        shape.setPosition(x, y);
        isActive = true;
    }

    void render(sf::RenderWindow& window)
    {
        if (isActive) {
            window.draw(shape);
        }
    }
};

class Game {
private:
    sf::RenderWindow window;
    sf::CircleShape shooter;
    sf::Vector2f shooterPos;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    bool gameWon = false;

    std::vector<Bubble> bubbles;  // Grid or stuck bubbles
    Bubble* currentShot = nullptr; // The flying bubble
    sf::Vector2f shotVelocity;     // Direction & speed of the shot

public:
    Game()
        : window(sf::VideoMode(800, 600), "Bubble Shooter"), shooterPos(400, 550)
    {
        shooter.setRadius(15);
        shooter.setFillColor(sf::Color::Red);
        shooter.setPosition(shooterPos);
        setUpLevel();
        shooter.setFillColor(randomColor());
        setUpBubble();

        if (!backgroundTexture.loadFromFile("Backgrounds/BBGame.jpg")) {
            std::cout << "Failed to load background image!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);

        // Scale to window size if needed
        sf::Vector2u windowSize = window.getSize();
        sf::Vector2u textureSize = backgroundTexture.getSize();
        backgroundSprite.setScale(
            static_cast<float>(windowSize.x) / textureSize.x,
            static_cast<float>(windowSize.y) / textureSize.y
        );
    }

    void spawnBubble(float x, float y, sf::Color color)
    {
        bubbles.push_back(Bubble(x, y, 15, color));
    }

    void shootBubble()
    {
        if (gameWon) return;  // Don't allow shooting if game is won
        if (currentShot != nullptr) return; // Only one bubble can be in the air

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f dir(mousePos.x - shooterPos.x, mousePos.y - shooterPos.y);
        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        if (length == 0) return; // Avoid division by zero
        dir /= length;

        currentShot = new Bubble(shooterPos.x + 15, shooterPos.y, 15, shooter.getFillColor());
        shotVelocity = dir * 5.0f; // Set speed
    }

    void setUpBubble()
    {
        float radius = 15.0f;
        int rows = 5;
        int cols = 6;

        float bubbleSpacing = radius * 2;
        float totalWidth = cols * bubbleSpacing;
        float startX = (800 - totalWidth) / 2.0f;  // Center the grid
        float startY = 50.0f; // Starting near top

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

    void update()
    {
        if (currentShot) {
            currentShot->shape.move(shotVelocity); // Move the bubble

            sf::Vector2f pos = currentShot->shape.getPosition();

            // Wall bounce logic
            if (pos.x <= 0 || pos.x + currentShot->shape.getRadius() * 2 >= 800) {
                shotVelocity.x = -shotVelocity.x;  // Reverse the X velocity on collision
            }

            // Top of screen = miss
            if (pos.y < 0) {
                delete currentShot;
                currentShot = nullptr;
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
                        bubbles.push_back(*currentShot);
                    }

                    delete currentShot;
                    currentShot = nullptr;
                    shooter.setFillColor(randomColor());
                    return;
                }
            }
        }

        if (!gameWon && bubbles.empty()) {
            gameWon = true;
        }
    }

    void setUpLevel()
    {
        float radius = 15.f;
        float diameter = radius * 2;
        int rows = 5;
        int cols = 12;

        // Calculate total grid width and height
        float totalWidth = cols * diameter;
        float totalHeight = rows * diameter;

        // Centering the grid on the screen
        float startX = (800 - totalWidth) / 2.0f;  // Center horizontally
        float startY = (600 - totalHeight) / 2.0f; // Center vertically

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                // Offset every other row for staggered pattern
                float x = startX + col * diameter;
                float y = startY + row * diameter;

                if (row % 2 == 1) {
                    x += radius;  // Offset every other row to form a triangular pattern
                }

                // Random colors for bubbles
                sf::Color color = randomColor();

                spawnBubble(x, y, color);
            }
        }
    }

    void render()
    {
        window.clear();

        window.draw(backgroundSprite); // Draw the background first

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
        if (gameWon) {
            sf::Font font;
            if (font.loadFromFile("assets/arial.ttf")) { // You can use any font you have
                sf::Text winText("You Win!", font, 50);
                winText.setFillColor(sf::Color::Green);
                winText.setStyle(sf::Text::Bold);
                winText.setPosition(800 / 2 - 100, 600 / 2 - 50);
                window.draw(winText);
            }
        }

        window.display();
    }

    void handling()
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    shootBubble();
                }
            }
        }
    }

    bool isRunning()
    {
        return window.isOpen();
    }

    void popMatchingBubbles(size_t index)
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

        // Pop the bubbles
        for (auto i : toPop) {
            bubbles[i].isActive = false;
        }

        // Remove popped bubbles
        bubbles.erase(std::remove_if(bubbles.begin(), bubbles.end(),
            [](const Bubble& b) { return !b.isActive; }), bubbles.end());
    }

    sf::Color randomColor()
    {
        int r = rand() % 3;
        switch (r) {
        case 0: return sf::Color::White;
        case 1: return sf::Color::Magenta;
        case 2: return sf::Color::Yellow;
        }
        return sf::Color::White;
    }
};
