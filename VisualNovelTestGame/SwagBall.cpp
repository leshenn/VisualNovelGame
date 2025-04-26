#include "SwagBall.h"

// Static variables
sf::Texture SwagBall::grapeTexture;
sf::Texture SwagBall::harmfulTexture;
bool SwagBall::texturesLoaded = false;

SwagBall::SwagBall(const sf::RenderWindow& window, int type)
    : type(type)
{
    if (!texturesLoaded)
        loadTextures();

    this->initSprite();

    // Random position within window bounds
    this->sprite.setPosition(
        static_cast<float>(rand() % (window.getSize().x - static_cast<int>(this->sprite.getGlobalBounds().width))),
        static_cast<float>(rand() % (window.getSize().y - static_cast<int>(this->sprite.getGlobalBounds().height)))
    );
}

SwagBall::~SwagBall()
{
}

void SwagBall::loadTextures()
{
    if (!grapeTexture.loadFromFile("WineAssets/grape.png"))
        std::cerr << "Error loading grape.png" << std::endl;

    if (!harmfulTexture.loadFromFile("WineAssets/harmful.png"))
        std::cerr << "Error loading harmful.png" << std::endl;

    texturesLoaded = true;
}

void SwagBall::initSprite()
{
    if (this->type == GRAPE)
        this->sprite.setTexture(grapeTexture);
    else
        this->sprite.setTexture(harmfulTexture);

    this->sprite.setScale(0.25f, 0.25f); // Adjust scale as needed
}

const sf::Sprite& SwagBall::getSprite() const
{
    return this->sprite;
}

const int& SwagBall::getType() const
{
    return this->type;
}

void SwagBall::update()
{
    // Nothing to update yet
}

void SwagBall::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}
