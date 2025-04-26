#include "WinePlayer.h"
#include <iostream>

void WinePlayer::initVariables()
{
    this->movementSpeed = 7.f;
    this->hpMax = 10;
    this->hp = hpMax;
}

void WinePlayer::initSprite()
{
    // Load the WinePlayer texture (make sure the file path is correct)
    if (!this->texture.loadFromFile("WineAssets/cup.png"))  // Change to your actual path
    {
        // Error loading texture
        std::cerr << "Error loading WinePlayer texture!" << std::endl;
    }

    // Apply texture to sprite
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(0.4f, 0.4f); // Smaller cup
    this->sprite.setPosition(100.f, 100.f);  // Set a default position for the WinePlayer
}

WinePlayer::WinePlayer()
{
    this->initVariables();
    this->initSprite();
}

WinePlayer::WinePlayer(float x, float y)
{
    this->sprite.setPosition(x, y);
    this->initVariables();
    this->initSprite();
}

WinePlayer::~WinePlayer() {}

const sf::Sprite& WinePlayer::getSprite() const
{
    return this->sprite;
}

const int& WinePlayer::getHp() const
{
    return this->hp;
}

const int& WinePlayer::getHpMax() const
{
    return this->hpMax;
}

void WinePlayer::takeDamage(const int damage)
{
    if (this->hp > 0)
        this->hp -= damage;

    if (this->hp < 0)
        this->hp = 0;
}

void WinePlayer::gainHealth(const int health)
{
    if (this->hp < this->hpMax)
        this->hp += health;

    if (this->hp > this->hpMax)
        this->hp = this->hpMax;
}

void WinePlayer::updateInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->sprite.move(-this->movementSpeed, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->sprite.move(this->movementSpeed, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->sprite.move(0.f, -this->movementSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->sprite.move(0.f, this->movementSpeed);
    }
}

void WinePlayer::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
    if (this->sprite.getGlobalBounds().left <= 0.f)
        this->sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);
    if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= target->getSize().x)
        this->sprite.setPosition(target->getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
    if (this->sprite.getGlobalBounds().top <= 0.f)
        this->sprite.setPosition(this->sprite.getGlobalBounds().left, 0.f);
    if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= target->getSize().y)
        this->sprite.setPosition(this->sprite.getGlobalBounds().left, target->getSize().y - this->sprite.getGlobalBounds().height);
}

void WinePlayer::update(const sf::RenderTarget* target)
{
    this->updateInput();
    this->updateWindowBoundsCollision(target);
}

void WinePlayer::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
}

