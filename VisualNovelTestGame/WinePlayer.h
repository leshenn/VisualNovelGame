#pragma once

#include <SFML/Graphics.hpp>

class WinePlayer
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float movementSpeed;
    int hpMax;
    int hp;

    void initVariables();
    void initSprite();

public:
    // Default constructor
    WinePlayer();
    // Constructor with position
    WinePlayer(float x, float y);
    ~WinePlayer();

    // Accessors
    const sf::Sprite& getSprite() const;
    const int& getHp() const;
    const int& getHpMax() const;

    // Functions
    sf::Vector2f getPosition() const { return sprite.getPosition(); }
    void takeDamage(const int damage);
    void gainHealth(const int health);
    void updateInput();
    void updateWindowBoundsCollision(const sf::RenderTarget* target);
    void update(const sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
};