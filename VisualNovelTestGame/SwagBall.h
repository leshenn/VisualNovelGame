#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class SwagBall
{
private:
    int type; // 0 = grape, 1 = harmful
    sf::Sprite sprite;

    void initSprite();

    static sf::Texture grapeTexture;
    static sf::Texture harmfulTexture;
    static bool texturesLoaded;

    static void loadTextures();

public:
    enum BallTypes { GRAPE = 0, HARMFUL };

    SwagBall(const sf::RenderWindow& window, int type);
    ~SwagBall();

    const sf::Sprite& getSprite() const;
    const int& getType() const;

    void update();
    void render(sf::RenderTarget& target);
};


