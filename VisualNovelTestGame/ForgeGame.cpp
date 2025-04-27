#include "ForgeGame.h"
#include <iostream>

ForgeGame::ForgeGame()
    : score(0)
    , activeHotspots(0)
    , heatLevel(0.f)
    , coolingRate(5.f)
    , gameOver(false)
    , baseSpawnTime(1.5f)
    , minSpawnTime(0.3f)
    , spawnTimeDecrease(0.04f)
    , currentSpawnTime(baseSpawnTime)
    , difficultyTimer(0.f)
    , hotspotTimer(0.f)
    , hammerRotation(0.f)
{
    // Seed random number generator once
    srand(static_cast<unsigned>(time(nullptr)));

    initWindow();
    initResources();
    initGameObjects();
    initUI();
}

ForgeGame::~ForgeGame()
{
    // Destructor - SFML objects handle their own cleanup
}

void ForgeGame::initWindow()
{
    window.create(sf::VideoMode(800, 600), "Sword Forging!");
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
}

void ForgeGame::initResources()
{
    // Load font
    if (!font.loadFromFile("ForgeGame/arial.ttf")) {
        sf::err() << "Failed to load font, using default\n";
    }

    // Load background image
    if (!backgroundTexture.loadFromFile("ForgeGame/forge_background.jpg")) {
        sf::err() << "Failed to load background image, creating gradient\n";
        backgroundTexture.create(800, 600);
        sf::Uint8* bgPixels = new sf::Uint8[800 * 600 * 4];
        for (int y = 0; y < 600; y++) {
            for (int x = 0; x < 800; x++) {
                int i = (y * 800 + x) * 4;
                bgPixels[i] = 30 + y / 8;
                bgPixels[i + 1] = 20 + y / 12;
                bgPixels[i + 2] = 10 + y / 16;
                bgPixels[i + 3] = 255;
            }
        }
        backgroundTexture.update(bgPixels);
        delete[] bgPixels;
    }

    // Load hammer texture
    if (!hammerTexture.loadFromFile("ForgeGame/hammer.png")) {
        sf::err() << "Failed to load hammer texture, creating placeholder\n";
        hammerTexture.create(64, 64);
        sf::Uint8* hammerPixels = new sf::Uint8[64 * 64 * 4];
        for (int y = 0; y < 64; y++) {
            for (int x = 0; x < 64; x++) {
                int i = (y * 64 + x) * 4;
                if (x < 10 || y < 10 || (x > 40 && y > 40)) {
                    hammerPixels[i] = 150; hammerPixels[i + 1] = 100; hammerPixels[i + 2] = 50; hammerPixels[i + 3] = 255;
                }
                else {
                    hammerPixels[i] = 200; hammerPixels[i + 1] = 150; hammerPixels[i + 2] = 100; hammerPixels[i + 3] = 255;
                }
            }
        }
        hammerTexture.update(hammerPixels);
        delete[] hammerPixels;
    }

    // Create hotspot texture (Procedural)
    hotspotTexture.create(30, 30);
    sf::Uint8* hotspotPixels = new sf::Uint8[30 * 30 * 4];
    for (int y = 0; y < 30; y++) {
        for (int x = 0; x < 30; x++) {
            int i = (y * 30 + x) * 4;
            float dist = std::sqrt((x - 15) * (x - 15) + (y - 15) * (y - 15));
            if (dist <= 15) {
                hotspotPixels[i] = 255;
                hotspotPixels[i + 1] = static_cast<sf::Uint8>(100 + (1 - dist / 15) * 155);
                hotspotPixels[i + 2] = 0;
                hotspotPixels[i + 3] = 200;
            }
            else {
                hotspotPixels[i] = hotspotPixels[i + 1] = hotspotPixels[i + 2] = hotspotPixels[i + 3] = 0;
            }
        }
    }
    hotspotTexture.update(hotspotPixels);
    delete[] hotspotPixels;


    // Load sounds
    if (!hitBuffer.loadFromFile("ForgeGame/hammer_hit.wav")) {
        sf::err() << "Failed to load hit sound\n";
    }
    else {
        hitSound.setBuffer(hitBuffer);
    }

    // Load music
    if (!forgeMusic.openFromFile("ForgeGame/forge_sounds.ogg")) {
        sf::err() << "Failed to load forge music\n";
    }
    else {
        forgeMusic.setLoop(true);
        forgeMusic.play();
    }
}

void ForgeGame::initGameObjects()
{
    // Background sprite
    background.setTexture(backgroundTexture);
    background.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    // Sword Blade
    swordBlade.setSize(sf::Vector2f(100.f, 525.f));
    swordBlade.setFillColor(sf::Color(200, 200, 220));
    swordBlade.setOutlineThickness(1.f);
    swordBlade.setOutlineColor(sf::Color(180, 180, 180));
    swordBlade.setOrigin(swordBlade.getSize().x / 2.f, swordBlade.getSize().y / 2.f);
    swordBlade.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    // Top Vice
    topVice.setSize(sf::Vector2f(150.f, 50.f));
    topVice.setFillColor(sf::Color(100, 100, 100));
    topVice.setOutlineThickness(2.f);
    topVice.setOutlineColor(sf::Color(70, 70, 70));
    topVice.setOrigin(topVice.getSize().x / 2.f, topVice.getSize().y / 2.f);
    topVice.setPosition(window.getSize().x / 2.f, 50.f);

    // Sword Point (Triangle)
    swordPoint.setPointCount(3);
    swordPoint.setPoint(0, sf::Vector2f(0, 0));
    swordPoint.setPoint(1, sf::Vector2f(30, 50));
    swordPoint.setPoint(2, sf::Vector2f(-30, 50));
    swordPoint.setFillColor(sf::Color(220, 220, 240));
    swordPoint.setOutlineThickness(1.f);
    swordPoint.setOutlineColor(sf::Color(180, 180, 180));
    swordPoint.setOrigin(0, 50); // Center bottom origin
    swordPoint.setPosition(topVice.getPosition().x, topVice.getPosition().y - topVice.getSize().y / 2);

    // Bottom Vice (Anvil-like)
    bottomVice.setSize(sf::Vector2f(150.f, 50.f));
    bottomVice.setFillColor(sf::Color(100, 100, 100));
    bottomVice.setOutlineThickness(2.f);
    bottomVice.setOutlineColor(sf::Color(70, 70, 70));
    bottomVice.setOrigin(bottomVice.getSize().x / 2.f, bottomVice.getSize().y / 2.f);
    bottomVice.setPosition(window.getSize().x / 2.f, window.getSize().y - 50.f);

    // Sword Handle
    swordHandle.setSize(sf::Vector2f(40.f, 80.f));
    swordHandle.setFillColor(sf::Color(100, 70, 40));
    swordHandle.setOrigin(swordHandle.getSize().x / 2.f, 0); // Origin at top center
    swordHandle.setPosition(bottomVice.getPosition().x, bottomVice.getPosition().y + bottomVice.getSize().y / 2);


    // Hammer sprite
    hammer.setTexture(hammerTexture);
    float hammerScale = 0.7f * (window.getSize().y * 0.1f) / hammerTexture.getSize().y;
    hammer.setScale(hammerScale, hammerScale);
    hammer.setOrigin(hammerTexture.getSize().x / 2.f, hammerTexture.getSize().y / 2.f);
}

void ForgeGame::initUI()
{
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);
    scoreText.setString("Score: 0");

    heatText.setFont(font);
    heatText.setCharacterSize(24);
    heatText.setFillColor(sf::Color::White);
    heatText.setPosition(10.f, 40.f);
    heatText.setString("Heat: 0%");

    hotspotText.setFont(font);
    hotspotText.setCharacterSize(24);
    hotspotText.setFillColor(sf::Color::White);
    hotspotText.setPosition(static_cast<float>(window.getSize().x) - 200.f, 10.f); // Position from right
    hotspotText.setString("Hotspots: 0/10");

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(36);
    gameOverText.setFillColor(sf::Color::Yellow);
    gameOverText.setPosition(static_cast<float>(window.getSize().x) / 2.f - 200.f, static_cast<float>(window.getSize().y) / 2.f - 50.f); // Center roughly
    gameOverText.setString(""); // Initially empty
}

void ForgeGame::run()
{
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        processEvents();
        if (!gameOver) {
            update(deltaTime);
        }
        render();
    }
}

void ForgeGame::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        // Close on Escape key if game over
        if (gameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left &&
            !gameOver)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            handleMouseClick(mousePos);
        }
    }
}

void ForgeGame::update(float deltaTime)
{
    updateDifficulty(deltaTime);
    updateHeat(deltaTime);
    updateHotspots(deltaTime);
    updateParticles(deltaTime);
    updateUI();
    updateHammer(); // Update hammer state based on click/movement

    checkGameOverConditions(); // Check after all updates
}

void ForgeGame::render()
{
    window.clear();

    renderBackground();
    renderSword();
    renderHotspots();
    renderParticles();
    renderUI();
    renderHammer(); // Draw hammer last so it's on top

    if (gameOver)
        window.draw(gameOverText);

    window.display();
}

void ForgeGame::updateDifficulty(float deltaTime)
{
    difficultyTimer += deltaTime;
    if (difficultyTimer >= 1.0f) { // Every second
        currentSpawnTime = std::max(minSpawnTime, currentSpawnTime - spawnTimeDecrease);
        difficultyTimer = 0.f;
    }
}

void ForgeGame::updateHeat(float deltaTime)
{
    // Cooling
    heatLevel -= coolingRate * deltaTime;
    if (heatLevel < 0.f) heatLevel = 0.f;

    // Visual effect - sword color changes with heat
    int heatColorBase = 220; // Starting base for non-red components
    int redComponent = std::min(255, 200 + static_cast<int>(heatLevel * 0.7f));
    int otherComponent = std::max(0, heatColorBase - static_cast<int>(heatLevel * 1.2f)); // Decrease green/blue

    swordBlade.setFillColor(sf::Color(redComponent, otherComponent, otherComponent));
    swordPoint.setFillColor(sf::Color(redComponent, otherComponent, otherComponent)); // Apply to point as well
    swordBlade.setOutlineThickness(1.f + (heatLevel / 100.f) * 3.f);
}

void ForgeGame::updateHotspots(float deltaTime)
{
    hotspotTimer += deltaTime;

    // Spawn new hotspots (using currentSpawnTime)
    if (hotspotTimer >= currentSpawnTime && activeHotspots < maxActiveHotspots)
    {
        hotspotTimer = 0.f;

        // Find a random valid position on the sword blade
        sf::FloatRect swordBounds = swordBlade.getGlobalBounds();
        float minX = swordBounds.left + 20; // Add padding
        float maxX = swordBounds.left + swordBounds.width - 40; // Subtract padding
        float minY = swordBounds.top + 30; // Add padding for the point
        float maxY = swordBounds.top + swordBounds.height - 30; // Subtract padding

        float x = minX + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxX - minX)));
        float y = minY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxY - minY)));

        Hotspot newHotspot;
        newHotspot.sprite.setTexture(hotspotTexture);
        float hotspotScale = (swordBlade.getSize().y * 0.08f) / hotspotTexture.getSize().y;
        newHotspot.sprite.setScale(hotspotScale, hotspotScale);
        newHotspot.sprite.setOrigin(hotspotTexture.getSize().x / 2.f, hotspotTexture.getSize().y / 2.f);
        newHotspot.sprite.setPosition(x, y);
        newHotspot.isVisible = true;
        newHotspot.activeTime = 0.f;
        newHotspot.position = sf::Vector2f(x, y); // Store base position

        hotspots.push_back(newHotspot);
        activeHotspots++;
    }

    // Update existing hotspots
    for (auto& hotspot : hotspots)
    {
        if (hotspot.isVisible)
        {
            hotspot.activeTime += deltaTime;
            // Pulsing scale effect
            float scale = 0.8f + 0.2f * std::sin(5 * hotspot.activeTime);
            float baseScale = (swordBlade.getSize().y * 0.08f) / hotspotTexture.getSize().y; // Recalculate in case window resizes? Or make swordScale fixed?
            hotspot.sprite.setScale(baseScale * scale, baseScale * scale);

            // Oscillating position effect
            float offsetX = 2.f * std::sin(2 * hotspot.activeTime);
            float offsetY = 2.f * std::cos(3 * hotspot.activeTime);
            hotspot.sprite.setPosition(hotspot.position.x + offsetX, hotspot.position.y + offsetY);
        }
    }

    // Remove inactive hotspots (handled in handleMouseClick by setting isVisible = false)
    // We need to sweep and remove them periodically or at the end of the frame
    hotspots.erase(
        std::remove_if(hotspots.begin(), hotspots.end(),
            [](const Hotspot& h) { return !h.isVisible; }),
        hotspots.end());

    // Update activeHotspots count manually after removal
    activeHotspots = 0;
    for (const auto& h : hotspots) {
        if (h.isVisible) activeHotspots++;
    }
}

void ForgeGame::updateParticles(float deltaTime)
{
    for (auto it = particles.begin(); it != particles.end(); ) {
        it->lifetime -= deltaTime;
        it->shape.move(it->velocity * deltaTime);
        it->velocity.y += 200.f * deltaTime; // Gravity (increased slightly)

        // Fade out
        float alpha = (it->lifetime / particleLifetime) * 255;
        if (alpha < 0) alpha = 0;
        sf::Color color = it->shape.getFillColor();
        color.a = static_cast<sf::Uint8>(alpha);
        it->shape.setFillColor(color);

        if (it->lifetime <= 0.f) {
            it = particles.erase(it);
        }
        else {
            ++it;
        }
    }
}

void ForgeGame::updateUI()
{
    scoreText.setString("Score: " + std::to_string(score));
    heatText.setString("Heat: " + std::to_string(static_cast<int>(heatLevel)) + "%");
    hotspotText.setString("Hotspots: " + std::to_string(activeHotspots) + "/10");


}

void ForgeGame::updateHammer()
{
    // Update hammer position to follow mouse
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    hammer.setPosition(mousePos);

    // Apply bounce effect when hitting (hammerRotation is set negatively in handleMouseClick)
    if (hammerRotation < 0) {
        hammerRotation += 300.f * clock.getElapsedTime().asSeconds(); // Increase rotation back towards 0
        if (hammerRotation > 0) hammerRotation = 0; // Prevent overshooting
    }
    hammer.setRotation(hammerRotation);
}


void ForgeGame::renderBackground()
{
    window.draw(background);
}

void ForgeGame::renderSword()
{
    window.draw(swordBlade);
    window.draw(topVice);
    window.draw(bottomVice);
    window.draw(swordPoint);

    // Draw handle stripes (moved from main loop)
    for (int i = 0; i < 8; i++) {
        sf::RectangleShape stripe(sf::Vector2f(40.f, 3.f));
        stripe.setFillColor(sf::Color(100, 100, 220)); // Blueish stripes for contrast
        stripe.setPosition(
            bottomVice.getPosition().x - 20,
            bottomVice.getPosition().y + bottomVice.getSize().y / 2 + i * 10
        );
        window.draw(stripe);
    }
    window.draw(swordHandle);
}

void ForgeGame::renderHotspots()
{
    for (auto& hotspot : hotspots)
        if (hotspot.isVisible)
            window.draw(hotspot.sprite);
}

void ForgeGame::renderParticles()
{
    sf::RenderStates sparkBlend;
    sparkBlend.blendMode = sf::BlendAdd; // Creates additive blending for glow

    for (auto& p : particles) {
        window.draw(p.shape, sparkBlend);
    }
}

void ForgeGame::renderUI()
{
    window.draw(scoreText);
    window.draw(heatText);
    window.draw(hotspotText);
    // Game over text is drawn directly in render() if gameOver is true
}

void ForgeGame::renderHammer()
{
    window.draw(hammer);
}

void ForgeGame::CreateSparks(sf::Vector2f position, int count) {
    for (int i = 0; i < count; i++) {
        Particle p;
        p.shape.setRadius(2.f + (rand() % 4)); // Slightly smaller sparks
        p.shape.setFillColor(sf::Color(255, 180 + rand() % 75, 0, 255)); // More orange/yellow

        // Start sparks near the hit position with small random offset
        p.shape.setPosition(
            position.x + (rand() % 6 - 3),
            position.y + (rand() % 6 - 3)
        );

        // Spread sparks in a wider angle (e.g., 180 degrees upwards/outwards)
        float angle = (rand() % 180 - 90) * 3.14159f / 180.f; // -90 to +90 degrees (upwards cone)
        if (rand() % 2 == 0) angle += 180 * 3.14159f / 180.f; // Randomly flip direction for wider spread

        float speed = 100.f + (rand() % 150); // Slower initial speed
        p.velocity = sf::Vector2f(cos(angle) * speed, sin(angle) * speed);
        p.lifetime = 0.4f * (0.6f + (rand() % 40) / 100.f); // Shorter lifetime, less variation

        particles.push_back(p);
    }
}


void ForgeGame::handleMouseClick(sf::Vector2f mousePos)
{
    bool hit = false;
    for (auto& hotspot : hotspots)
    {
        if (hotspot.isVisible && hotspot.sprite.getGlobalBounds().contains(mousePos))
        {
            CreateSparks(mousePos, 10);
            hotspot.isVisible = false; // Mark for removal
            // activeHotspots count will be updated in updateHotspots clean-up
            score += 10;
            heatLevel += 15.f; // Less heat per hit
            if (heatLevel > 100.f) heatLevel = 100.f;
            hitSound.play();
            hit = true;

            // Apply hammer bounce rotation
            hammerRotation = -45.f; // Rotate backward slightly
            break; // Assume only hit one hotspot per click
        }
    }

    if (!hit)
    {
        heatLevel -= 5.f; // Less penalty for miss
        if (heatLevel < 0.f) heatLevel = 0.f;
        hitSound.play(); // Play sound even on miss
        hammerRotation = -10.f; // Small bounce on miss
    }
}

int ForgeGame::getScore() { return score; };

void ForgeGame::checkGameOverConditions()
{
    if (heatLevel >= 100.f) {
        gameOver = true;
        gameOverText.setString("Sword Overheated!\nFinal Score: " + std::to_string(score) + "\n\nPress ESC to Exit");
        forgeMusic.stop();
    }

    // activeHotspots is updated in updateHotspots after removal, check against it
    if (activeHotspots >= maxHotspots && !gameOver) { // Only game over if not already overheated
        gameOver = true;
        gameOverText.setString("Too Many Imperfections!\nFinal Score: " + std::to_string(score) + "\n\nPress ESC to Exit");
        forgeMusic.stop();
    }

    // Center the game over text
    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    gameOverText.setPosition(static_cast<float>(window.getSize().x) / 2.0f,
        static_cast<float>(window.getSize().y) / 2.0f);
}