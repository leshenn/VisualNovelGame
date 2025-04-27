#include "WineGame.h"

void WineGame::initVariables()
{
    this->endGame = false;
    this->spawnTimerMax = 5.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxSwagBalls = 20;
    this->points = 0;
    this->damagingItems = 0;  // Track harmful items collected
}

void WineGame::initWindow()
{

    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "Wine Collector", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);




    if (!backgroundTexture.loadFromFile("WineAssets/winebackground.jpg")) {
        std::cerr << "Error loading background.png" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    // Calculate scale factors to fit the window size
    float scaleX = 800.0f / backgroundTexture.getSize().x;
    float scaleY = 600.0f / backgroundTexture.getSize().y;

    // Apply the scaling
    backgroundSprite.setScale(scaleX, scaleY);

    // Audio init
    auto devices = sf::SoundRecorder::getAvailableDevices();
    std::cout << "Audio devices detected:\n";
    for (const auto& device : devices) {
        std::cout << "- " << device << std::endl;
    }
    sf::SoundBuffer dummyBuffer;
    dummyBuffer.loadFromFile("WineAssets/grape_collect.wav");

}

void WineGame::initFonts()
{
    if (!this->font.loadFromFile("WineAssets/PixellettersFull.ttf"))
    {
        std::cout << " ! ERROR::WineGame::INITFONTS::COULD NOT LOAD PixellettersFull.ttf" << "\n";
    }
}

void WineGame::initText()
{
    // Gui text init
    this->guiText.setFont(this->font);
    this->guiText.setFillColor(sf::Color::White);
    this->guiText.setCharacterSize(32);

    timerText.setFont(font);
    timerText.setCharacterSize(24);
    timerText.setPosition(10, 10);

    // Win text setup
    winText.setFont(font);
    winText.setString("YOU WIN! Press ESC to exit");
    winText.setCharacterSize(60);
    winText.setFillColor(sf::Color::Green);
    winText.setPosition(
        window->getSize().x / 2 - winText.getLocalBounds().width / 2,
        window->getSize().y / 2 - winText.getLocalBounds().height / 2
    );

    // NEW: Lose Text
    loseText.setFont(font);
    loseText.setString("YOU LOST! Wine spoiled (ESC to exit)");
    loseText.setCharacterSize(60);
    loseText.setFillColor(sf::Color::Red);
    loseText.setPosition(
        window->getSize().x / 2 - loseText.getLocalBounds().width / 2,
        window->getSize().y / 2 - loseText.getLocalBounds().height / 2
    );


}

WineGame::WineGame()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->GameWon = false;

    if (grapeSoundBuffer.loadFromFile("WineAssets/grape_collect.wav")) {
        grapeSound.setBuffer(grapeSoundBuffer);
        grapeSound.play();
        sf::sleep(sf::milliseconds(100)); // Keep this delay
        std::cout << "Constructor sound status: " << grapeSound.getStatus() << std::endl;
    }
    musicPlaying = false;
    initSounds();
}

WineGame::~WineGame()
{
    delete this->window;
}

const bool& WineGame::getEndGame() const
{
    return this->endGame;
}

const bool WineGame::running() const
{
    return this->window->isOpen();
}

void WineGame::pollEvents()
{
    while (this->window->pollEvent(this->sfmlEvent))
    {
        switch (this->sfmlEvent.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void WineGame::spawnSwagBalls()
{
    if (this->spawnTimer < this->spawnTimerMax)
        this->spawnTimer += 1.f;
    else
    {
        if (this->swagBalls.size() < this->maxSwagBalls)
        {
            this->swagBalls.push_back(SwagBall(*this->window, this->randBallType()));

            this->spawnTimer = 0.f;
        }
    }
}

const int WineGame::randBallType() const
{
    int type = 0; // Default is grape

    int randValue = rand() % 100 + 1;
    if (randValue > 60 && randValue <= 80)
        type = 1; // Harmful item (spoiler)

    return type;
}

void WineGame::updateWinePlayer()
{
    this->WinePlayer.update(this->window);

    if (this->WinePlayer.getHp() <= 0)
        this->endGame = true;
}

void WineGame::updateCollision()
{
    if (this->points >= 50)
    {
        this->GameWon = true;
    }

    for (size_t i = 0; i < this->swagBalls.size(); i++)
    {
        if (this->WinePlayer.getSprite().getGlobalBounds().intersects(this->swagBalls[i].getSprite().getGlobalBounds()))
        {
            switch (this->swagBalls[i].getType())
            {
            case 0: // Grape
            {
                this->points++;
                grapeSound.play();

                // Create effect at player position - now in a scoped block
                sf::CircleShape effect(10.f);
                effect.setFillColor(sf::Color(255, 50, 50, 200)); // Gold color with transparency
                effect.setPosition(
                    WinePlayer.getPosition().x + WinePlayer.getSprite().getGlobalBounds().width / 2 - 10.f,
                    WinePlayer.getPosition().y + WinePlayer.getSprite().getGlobalBounds().height / 2 - 10.f
                );
                collectionEffects.push_back(effect);
                break;
            }
            case 1: // Harmful item
                this->damagingItems++;
                harmfulSound.play();
                if (damagingItems >= 5 && !gameLost) {
                    gameLost = true;
                }
                break;
            }

            // Remove the ball from the WineGame
            this->swagBalls.erase(this->swagBalls.begin() + i);
        }
    }
}

void WineGame::updateGui()
{
    std::stringstream ss;

    ss << " - Grapes: " << this->points << "\n"
        << " - Harmful Items Collected: " << this->damagingItems << " / 5" << "\n";
    guiText.setString(ss.str());

}

void WineGame::update()
{
    this->pollEvents();

    float remainingTime = timeLimit - gameClock.getElapsedTime().asSeconds();
    if (remainingTime <= 0 && !GameWon) {
        gameLost = true; // Time's up!
    }

    if (!endGame && !GameWon)
    {
        this->spawnSwagBalls();
        this->updateWinePlayer();
        this->updateCollision();
        this->updateGui();
        for (auto& effect : collectionEffects) {
            float radius = effect.getRadius();
            if (radius > 0) {
                effect.setRadius(radius - 0.3f);
                sf::Color color = effect.getFillColor();
                color.a = static_cast<sf::Uint8>(color.a * 0.9f); // Fade out
                effect.setFillColor(color);
            }
        }

        // Remove finished effects
        collectionEffects.erase(
            std::remove_if(collectionEffects.begin(), collectionEffects.end(),
                [](const sf::CircleShape& effect) { return effect.getRadius() <= 0; }),
            collectionEffects.end());

        // Check if the player has spoiled the wine (collected 5 harmful items)
        if (this->damagingItems >= 5)
        {
            this->endGame = true;
        }
    }


}

void WineGame::renderGui(sf::RenderTarget* target)
{
    target->draw(this->guiText);
}

void WineGame::render()
{
    this->window->clear();

    window->draw(backgroundSprite);

    for (const auto& effect : collectionEffects) {
        window->draw(effect);
    }
    // Render end WineGame text if WineGame is over
    if (this->endGame == true)
        this->window->draw(this->endGameText);

    if (GameWon) {
        // Show win screen
        window->draw(winText);
    }
    else if (gameLost) {
        // Show lose screen (existing)
        window->draw(loseText);
    }
    else {
        // Normal WineGameplay rendering
        WinePlayer.render(window);
        for (auto& ball : swagBalls) {
            ball.render(*window);
        }
        renderGui(window);
    }

    this->window->display();

    if (this->GameWon)
    {
        sf::Font font;
        if (!font.loadFromFile("WineAssets/arial.ttf")) // Replace with your font path
        {
            std::cerr << "Failed to load font!" << std::endl;
        }
        else
        {
            sf::Text winText;
            winText.setFont(font);
            winText.setCharacterSize(60);
            winText.setFillColor(sf::Color::Yellow);
            winText.setStyle(sf::Text::Bold);
            winText.setString("You Win!");
            winText.setPosition(
                this->window->getSize().x / 2.f - winText.getGlobalBounds().width / 2.f,
                this->window->getSize().y / 2.f - winText.getGlobalBounds().height / 2.f
            );

            this->window->draw(winText);
        }
    }
}

bool WineGame::getGameWin() { return GameWon; };

void WineGame::initSounds() {
    if (!bgMusic.openFromFile("WineAssets/background_music.ogg")) {  // Use .ogg for music
        std::cerr << "ERROR: Failed to load background music!" << std::endl;
    }
    else {
        bgMusic.setLoop(true);
        bgMusic.setVolume(50.f);  // 50% volume
        bgMusic.play();
        musicPlaying = true;
        std::cout << "Background music started!" << std::endl;
    }

    if (!grapeSoundBuffer.loadFromFile("WineAssets/grape_collect.wav")) {
        std::cerr << "ERROR: Failed to load grape sound!" << std::endl;
    }
    else {
        grapeSound.setBuffer(grapeSoundBuffer); // Link buffer to sound
    }

    if (!harmfulSoundBuffer.loadFromFile("WineAssets/harmful.wav")) {  // Replace with your file
        std::cerr << "ERROR: Failed to load harmful sound!" << std::endl;
    }
    else {
        harmfulSound.setBuffer(harmfulSoundBuffer);
        harmfulSound.setVolume(70.f);
    }
    bgMusic.setVolume(50.f); // 50% volume (0-100)
    grapeSound.setVolume(70.f);
}
